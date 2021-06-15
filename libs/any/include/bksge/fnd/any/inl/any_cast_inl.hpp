/**
 *	@file	any_cast_inl.hpp
 *
 *	@brief	any_cast 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_INL_ANY_CAST_INL_HPP
#define BKSGE_FND_ANY_INL_ANY_CAST_INL_HPP

#include <bksge/fnd/any/any_cast.hpp>
#include <bksge/fnd/any/bad_any_cast.hpp>
#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
struct any::AnyCaster
{
	template <typename U, bool>
	struct Impl;

	template <typename U>
	struct Impl<U, true>
	{
		static void* invoke(any const* a)
		{
			if (a->m_manager == &any::Manager<bksge::decay_t<U>>::manage)
			{
				any::Arg arg;
				a->m_manager(any::OpAccess, a, &arg);
				return arg.m_obj;
			}
			return nullptr;
		}
	};

	template <typename U>
	struct Impl<U, false>
	{
		static void* invoke(any const*)
		{
			return nullptr;
		}
	};

	static void* do_cast(any const* a)
	{
		return Impl<T, bksge::is_copy_constructible<bksge::decay_t<T>>::value>::invoke(a);
	}
};

template <typename ValueType>
BKSGE_NODISCARD inline ValueType const*
any_cast(any const* a) BKSGE_NOEXCEPT
{
	if (a)
	{
		return static_cast<ValueType const*>(any::AnyCaster<ValueType>::do_cast(a));
	}
	return nullptr;
}

template <typename ValueType>
BKSGE_NODISCARD inline ValueType*
any_cast(any* a) BKSGE_NOEXCEPT
{
	if (a)
	{
		return static_cast<ValueType*>(any::AnyCaster<ValueType>::do_cast(a));
	}
	return nullptr;
}

namespace any_cast_detail
{

template <typename T>
struct IsValidCast
	: public bksge::disjunction<
		bksge::is_reference<T>,
		bksge::is_copy_constructible<T>
	>
{};

template <typename ValueType, typename AnyType>
inline ValueType* any_cast_impl(AnyType* a)
{
	auto p = bksge::any_cast<ValueType>(a);

	if (!p)
	{
		bksge::throw_bad_any_cast();
	}

	return p;
}

}	// namespace any_cast_detail

template <typename ValueType>
BKSGE_NODISCARD inline ValueType
any_cast(any const& a)
{
	static_assert(any_cast_detail::IsValidCast<ValueType>::value,
		"Template argument must be a reference or CopyConstructible type");
	using U = bksge::remove_cv_t<bksge::remove_reference_t<ValueType>>;
	return static_cast<ValueType>(*any_cast_detail::any_cast_impl<U const>(&a));
}

template <typename ValueType>
BKSGE_NODISCARD inline ValueType
any_cast(any& a)
{
	static_assert(any_cast_detail::IsValidCast<ValueType>::value,
		"Template argument must be a reference or CopyConstructible type");
	using U = bksge::remove_cv_t<bksge::remove_reference_t<ValueType>>;
	return static_cast<ValueType>(*any_cast_detail::any_cast_impl<U>(&a));
}

template <typename ValueType>
BKSGE_NODISCARD inline ValueType
any_cast(any&& a)
{
	static_assert(any_cast_detail::IsValidCast<ValueType>::value,
		"Template argument must be a reference or CopyConstructible type");
	using U = bksge::remove_cv_t<bksge::remove_reference_t<ValueType>>;
	return static_cast<ValueType>(bksge::move(*any_cast_detail::any_cast_impl<U>(&a)));
}

}	// namespace bksge

#endif // BKSGE_FND_ANY_INL_ANY_CAST_INL_HPP
