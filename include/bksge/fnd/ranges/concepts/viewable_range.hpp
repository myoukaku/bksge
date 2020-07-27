/**
 *	@file	viewable_range.hpp
 *
 *	@brief	viewable_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept viewable_range =
	ranges::range<T> &&
	(ranges::borrowed_range<T> || ranges::view<bksge::remove_cvref_t<T>>);

#else

template <typename T>
using viewable_range = bksge::conjunction<
	ranges::range<T>,
	bksge::disjunction<ranges::borrowed_range<T>, ranges::view<bksge::remove_cvref_t<T>>>
>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
