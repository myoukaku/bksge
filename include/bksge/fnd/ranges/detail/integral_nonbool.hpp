/**
 *	@file	integral_nonbool.hpp
 *
 *	@brief	integral_nonbool の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP
#define BKSGE_FND_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP

#include <bksge/fnd/ranges/detail/cv_bool.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept integral_nonbool =
	bksge::integral<T> &&
	!detail::cv_bool<T>;

#else

template <typename T>
using integral_nonbool = bksge::conjunction<
	bksge::integral<T>,
	bksge::negation<detail::cv_bool<T>>
>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP
