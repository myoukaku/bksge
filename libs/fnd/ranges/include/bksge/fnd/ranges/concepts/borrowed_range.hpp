/**
 *	@file	borrowed_range.hpp
 *
 *	@brief	borrowed_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_BORROWED_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_BORROWED_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept borrowed_range =
	ranges::range<T> &&
	detail::maybe_borrowed_range<T>;

template <typename T>
using is_borrowed_range = bksge::bool_constant<borrowed_range<T>>;

#else

template <typename T>
using borrowed_range = bksge::conjunction<
	ranges::range<T>,
	detail::maybe_borrowed_range<T>
>;

template <typename T>
using is_borrowed_range = borrowed_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_BORROWED_RANGE_HPP
