/**
 *	@file	same_as.hpp
 *
 *	@brief	same_as の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SAME_AS_HPP
#define BKSGE_FND_CONCEPTS_SAME_AS_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename U>
concept SameHelper = bksge::is_same<T, U>::value;

}	// namespace detail

template <typename T, typename U>
concept same_as =
	detail::SameHelper<T, U> &&
	detail::SameHelper<U, T>;

template <typename T, typename U>
using is_same_as = bksge::bool_constant<same_as<T, U>>;

#else

template <typename T, typename U>
using same_as =
	bksge::conjunction<
		bksge::is_same<T, U>,
		bksge::is_same<U, T>
	>;

template <typename T, typename U>
using is_same_as = same_as<T, U>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SAME_AS_HPP
