/**
 *	@file	any.hpp
 *
 *	@brief	any クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_ANY_HPP
#define BKSGE_FND_ANY_ANY_HPP

#include <bksge/fnd/any/config.hpp>

#if defined(BKSGE_USE_STD_ANY)

namespace bksge
{

using std::any;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <initializer_list>
#include <typeinfo>		// type_info

namespace bksge
{

/**
 *	@brief
 */
class any
{
private:
	template <typename T>
	using IsConstructible =
		bksge::conjunction<
			bksge::negation<bksge::is_same<T, any>>,
			bksge::is_copy_constructible<T>,
			bksge::negation<bksge::is_in_place_type<T>>
		>;

	template <typename T, typename... Args>
	using IsInPlaceConstructible =
		bksge::conjunction<
			bksge::is_constructible<T, Args...>,
			bksge::is_copy_constructible<T>
		>;

	template <typename T, typename U, typename... Args>
	using IsInitializerListConstructible =
		bksge::conjunction<
			bksge::is_constructible<T, std::initializer_list<U>&, Args...>,
			bksge::is_copy_constructible<T>
		>;

	template <typename T>
	using IsAssignable =
		bksge::conjunction<
			bksge::negation<bksge::is_same<T, any>>,
			bksge::is_copy_constructible<T>
		>;

public:
	BKSGE_CONSTEXPR any() BKSGE_NOEXCEPT;

	any(any const& other);

	any(any&& other) BKSGE_NOEXCEPT;

	template <
		typename ValueType,
		typename = bksge::enable_if_t<IsConstructible<bksge::decay_t<ValueType>>::value>
	>
	any(ValueType&& value);

	template <
		typename ValueType,
		typename... Args,
		typename = bksge::enable_if_t<IsInPlaceConstructible<bksge::decay_t<ValueType>, Args...>::value>
	>
	explicit any(bksge::in_place_type_t<ValueType>, Args&&... args);

	template <
		typename ValueType,
		typename U,
		typename... Args,
		typename = bksge::enable_if_t<IsInitializerListConstructible<bksge::decay_t<ValueType>, U, Args...>::value>
	>
	explicit any(bksge::in_place_type_t<ValueType>, std::initializer_list<U> il, Args&&... args);

	~any();

	any& operator=(any const& rhs);

	any& operator=(any&& rhs) BKSGE_NOEXCEPT;

	template <
		typename ValueType,
		typename = bksge::enable_if_t<IsAssignable<bksge::decay_t<ValueType>>::value>
	>
	any& operator=(ValueType&& rhs);

	template <
		typename ValueType,
		typename... Args,
		typename = bksge::enable_if_t<IsInPlaceConstructible<bksge::decay_t<ValueType>, Args...>::value>
	>
	bksge::decay_t<ValueType>& emplace(Args&&... args);

	template <
		typename ValueType,
		typename U,
		typename... Args,
		typename = bksge::enable_if_t<IsInitializerListConstructible<bksge::decay_t<ValueType>, U, Args...>::value>
	>
	bksge::decay_t<ValueType>& emplace(std::initializer_list<U> il, Args&&... args);

	void reset() BKSGE_NOEXCEPT;

	void swap(any& rhs) BKSGE_NOEXCEPT;

	bool has_value() const BKSGE_NOEXCEPT;

#if !defined(BKSGE_NO_RTTI)
	std::type_info const& type() const BKSGE_NOEXCEPT;
#endif

private:
	union Storage
	{
		BKSGE_CONSTEXPR Storage(): m_ptr{ nullptr } {}

		// Prevent trivial copies of this type, buffer might hold a non-POD.
		Storage(Storage const&) = delete;
		Storage& operator=(Storage const&) = delete;

		void* m_ptr;
//		bksge::aligned_storage<sizeof(void*), alignof(void*)>::type m_buffer;
		bksge::aligned_storage<sizeof(void*), bksge::alignment_of<void*>::value>::type m_buffer;
	};

	template <typename T>
	using IsInternal = bksge::bool_constant<
		bksge::is_nothrow_move_constructible<T>::value &&
		(sizeof(T)  <= sizeof(Storage))	&&
//		(alignof(T) <= alignof(Storage))
		(bksge::alignment_of<T>::value <= bksge::alignment_of<Storage>::value)
	>;

	template <typename T>
	struct ManagerInternal; // uses small-object optimization

	template <typename T>
	struct ManagerExternal; // creates contained object on the heap

	template <typename T>
	using Manager = bksge::conditional_t<IsInternal<T>::value,
		ManagerInternal<T>,
		ManagerExternal<T>>;

	template <typename T, typename... Args>
	void do_emplace(Args&&... args);

	enum Op
	{
		OpAccess,
		OpGetTypeInfo,
		OpClone,
		OpDestroy,
		OpXfer
	};

	union Arg
	{
		void* m_obj;
		std::type_info const* m_typeinfo;
		any* m_any;
	};

	void (*m_manager)(Op, any const*, Arg*);
	Storage m_storage;

	// Manage in-place contained object.
	template <typename T>
	struct ManagerInternal;

	// Manage external contained object.
	template <typename T>
	struct ManagerExternal;


	template <typename T>
	struct AnyCaster;

	template <typename ValueType>
	friend ValueType const* any_cast(any const*) BKSGE_NOEXCEPT;

	template <typename ValueType>
	friend ValueType* any_cast(any*) BKSGE_NOEXCEPT;
};

inline void swap(any& lhs, any& rhs) BKSGE_NOEXCEPT
{
	lhs.swap(rhs);
}

}	// namespace bksge

#include <bksge/fnd/any/inl/any_inl.hpp>

#endif

#endif // BKSGE_FND_ANY_ANY_HPP
