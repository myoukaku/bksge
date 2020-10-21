/**
 *	@file	builtin_ptr_three_way.hpp
 *
 *	@brief	builtin_ptr_three_way の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
#define BKSGE_FND_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

// BUILTIN-PTR-THREE-WAY(T, U)
template <typename T, typename U>
concept builtin_ptr_three_way =
	requires(T&& t, U&& u)
	{
		static_cast<T&&>(t) <=> static_cast<U&&>(u);
	} &&
	bksge::convertible_to<T, void const volatile*> &&
	bksge::convertible_to<U, void const volatile*> &&
	!requires(T&& t, U&& u)
	{
		operator<=>(static_cast<T&&>(t), static_cast<U&&>(u));
	} &&
	!requires(T&& t, U&& u)
	{
		static_cast<T&&>(t).operator<=>(static_cast<U&&>(u));
	};

#else

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
