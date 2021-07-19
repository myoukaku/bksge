/**
 *	@file	any_inl.hpp
 *
 *	@brief	any クラステンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_INL_ANY_INL_HPP
#define BKSGE_FND_ANY_INL_ANY_INL_HPP

#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>
#include <typeinfo>		// type_info
#include <utility>

namespace bksge
{

inline BKSGE_CONSTEXPR
any::any() BKSGE_NOEXCEPT
	: m_manager(nullptr)
{}

inline
any::any(any const& other)
{
	if (!other.has_value())
	{
		m_manager = nullptr;
	}
	else
	{
		Arg arg;
		arg.m_any = this;
		other.m_manager(OpClone, &other, &arg);
	}
}

inline
any::any(any&& other) BKSGE_NOEXCEPT
{
	if (!other.has_value())
	{
		m_manager = nullptr;
	}
	else
	{
		Arg arg;
		arg.m_any = this;
		other.m_manager(OpXfer, &other, &arg);
	}
}

template <typename ValueType, typename>
inline
any::any(ValueType&& value)
	: m_manager(&Manager<bksge::decay_t<ValueType>>::manage)
{
	Manager<bksge::decay_t<ValueType>>::create(m_storage, std::forward<ValueType>(value));
}

template <typename ValueType, typename... Args, typename>
inline
any::any(bksge::in_place_type_t<ValueType>, Args&&... args)
	: m_manager(&Manager<bksge::decay_t<ValueType>>::manage)
{
	Manager<bksge::decay_t<ValueType>>::create(m_storage, std::forward<Args>(args)...);
}

template <typename ValueType, typename U, typename... Args, typename>
inline
any::any(bksge::in_place_type_t<ValueType>, std::initializer_list<U> il, Args&&... args)
	: m_manager(&Manager<bksge::decay_t<ValueType>>::manage)
{
	Manager<bksge::decay_t<ValueType>>::create(m_storage, il, std::forward<Args>(args)...);
}

inline
any::~any()
{
	reset();
}

inline any&
any::operator=(any const& rhs)
{
	*this = any(rhs);
	return *this;
}

inline any&
any::operator=(any&& rhs) BKSGE_NOEXCEPT
{
	if (!rhs.has_value())
	{
		reset();
	}
	else if (this != &rhs)
	{
		reset();
		Arg arg;
		arg.m_any = this;
		rhs.m_manager(OpXfer, &rhs, &arg);
	}

	return *this;
}

template <typename ValueType, typename>
inline any&
any::operator=(ValueType&& rhs)
{
	*this = any(std::forward<ValueType>(rhs));
	return *this;
}

template <typename ValueType, typename... Args, typename>
inline bksge::decay_t<ValueType>&
any::emplace(Args&&... args)
{
	do_emplace<bksge::decay_t<ValueType>>(std::forward<Args>(args)...);
	any::Arg arg;
	this->m_manager(any::OpAccess, this, &arg);
	return *static_cast<bksge::decay_t<ValueType>*>(arg.m_obj);
}

template <typename ValueType, typename U, typename... Args, typename>
inline bksge::decay_t<ValueType>&
any::emplace(std::initializer_list<U> il, Args&&... args)
{
	do_emplace<bksge::decay_t<ValueType>>(il, std::forward<Args>(args)...);
	any::Arg arg;
	this->m_manager(any::OpAccess, this, &arg);
	return *static_cast<bksge::decay_t<ValueType>*>(arg.m_obj);
}

inline void
any::reset() BKSGE_NOEXCEPT
{
	if (has_value())
	{
		m_manager(OpDestroy, this, nullptr);
		m_manager = nullptr;
	}
}

inline void
any::swap(any& rhs) BKSGE_NOEXCEPT
{
	if (!has_value() && !rhs.has_value())
	{
		return;
	}

	if (has_value() && rhs.has_value())
	{
		if (this == &rhs)
		{
			return;
		}

		any tmp;
		Arg arg;
		arg.m_any = &tmp;
		rhs.m_manager(OpXfer, &rhs, &arg);
		arg.m_any = &rhs;
		m_manager(OpXfer, this, &arg);
		arg.m_any = this;
		tmp.m_manager(OpXfer, &tmp, &arg);
	}
	else
	{
		any* empty = !has_value() ? this : &rhs;
		any* full = !has_value() ? &rhs : this;
		Arg arg;
		arg.m_any = empty;
		full->m_manager(OpXfer, full, &arg);
	}
}

inline bool
any::has_value() const BKSGE_NOEXCEPT
{
	return m_manager != nullptr;
}

#if !defined(BKSGE_NO_RTTI)

inline std::type_info const&
any::type() const BKSGE_NOEXCEPT
{
	if (!has_value())
	{
		return typeid(void);
	}

	Arg arg;
	m_manager(OpGetTypeInfo, this, &arg);
	return *arg.m_typeinfo;
}

#endif

template <typename T, typename... Args>
inline void
any::do_emplace(Args&&... args)
{
	reset();
	m_manager = &Manager<T>::manage;
	Manager<T>::create(m_storage, std::forward<Args>(args)...);
}

template <typename T>
struct any::ManagerInternal
{
	static void manage(Op which, any const* a, Arg* arg)
	{
		auto ptr = reinterpret_cast<T const*>(&a->m_storage.m_buffer);
		switch (which)
		{
		case OpAccess:
			arg->m_obj = const_cast<T*>(ptr);
			break;
		case OpGetTypeInfo:
#if !defined(BKSGE_NO_RTTI)
			arg->m_typeinfo = &typeid(T);
#endif
			break;
		case OpClone:
			::new(&arg->m_any->m_storage.m_buffer) T(*ptr);
			arg->m_any->m_manager = a->m_manager;
			break;
		case OpDestroy:
			ptr->~T();
			break;
		case OpXfer:
			::new(&arg->m_any->m_storage.m_buffer) T(std::move(*const_cast<T*>(ptr)));
			ptr->~T();
			arg->m_any->m_manager = a->m_manager;
			const_cast<any*>(a)->m_manager = nullptr;
			break;
		}
	}

	template <
		typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, Args&&...>::value &&
			!bksge::disjunction<bksge::is_lvalue_reference<Args>...>::value
		>
	>
	static void create(Storage& storage, Args&&... args)
	{
		void* addr = &storage.m_buffer;
		::new (addr) T(std::forward<Args>(args)...);
	}

	template <
		typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, Args const&...>::value
		>
	>
	static void create(Storage& storage, Args const&... args)
	{
		void* addr = &storage.m_buffer;
		::new (addr) T(args...);
	}
};

template <typename T>
struct any::ManagerExternal
{
	static void manage(Op which, any const* a, Arg* arg)
	{
		auto ptr = static_cast<T const*>(a->m_storage.m_ptr);
		switch (which)
		{
		case OpAccess:
			arg->m_obj = const_cast<T*>(ptr);
			break;
		case OpGetTypeInfo:
#if !defined(BKSGE_NO_RTTI)
			arg->m_typeinfo = &typeid(T);
#endif
			break;
		case OpClone:
			arg->m_any->m_storage.m_ptr = new T(*ptr);
			arg->m_any->m_manager = a->m_manager;
			break;
		case OpDestroy:
			delete ptr;
			break;
		case OpXfer:
			arg->m_any->m_storage.m_ptr = a->m_storage.m_ptr;
			arg->m_any->m_manager = a->m_manager;
			const_cast<any*>(a)->m_manager = nullptr;
			break;
		}
	}

	template <
		typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, Args&&...>::value &&
			!bksge::disjunction<bksge::is_lvalue_reference<Args>...>::value
		>
	>
	static void create(Storage& storage, Args&&... args)
	{
		storage.m_ptr = new T(std::forward<Args>(args)...);
	}

	template <
		typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, Args const&...>::value
		>
	>
	static void create(Storage& storage, Args const&... args)
	{
		storage.m_ptr = new T(args...);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_ANY_INL_ANY_INL_HPP
