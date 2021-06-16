/**
 *	@file	span_compatible_range.hpp
 *
 *	@brief	span_compatible_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP
#define BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP

#include <bksge/fnd/span/detail/is_span_compatible_ref.hpp>
#include <bksge/fnd/span/detail/is_span.hpp>
#include <bksge/fnd/span/detail/is_std_array.hpp>
#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Range, typename T>
concept span_compatible_range =
	ranges::contiguous_range<Range> &&
	ranges::sized_range<Range> &&
	(ranges::borrowed_range<Range> || bksge::is_const<T>::value) &&
	(!detail::is_span<bksge::remove_cvref_t<Range>>::value) &&
	(!detail::is_std_array<bksge::remove_cvref_t<Range>>::value) &&
	(!bksge::is_array<bksge::remove_cvref_t<Range>>::value) &&
	detail::is_span_compatible_ref<T, ranges::range_reference_t<Range>>::value;

#else

template <typename Range, typename T>
using span_compatible_range = bksge::conjunction<
	ranges::contiguous_range<Range>,
	ranges::sized_range<Range>,
	bksge::disjunction<ranges::borrowed_range<Range>, bksge::is_const<T>>,
	bksge::negation<detail::is_span<bksge::remove_cvref_t<Range>>>,
	bksge::negation<detail::is_std_array<bksge::remove_cvref_t<Range>>>,
	bksge::negation<bksge::is_array<bksge::remove_cvref_t<Range>>>,
	detail::is_span_compatible_ref<T, ranges::range_reference_t<Range>>
>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_RANGE_HPP
