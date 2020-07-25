/**
 *	@file	span_compatible_iterator.hpp
 *
 *	@brief	span_compatible_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP
#define BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP

#include <bksge/fnd/span/detail/is_span_compatible_ref.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename It, typename T>
concept span_compatible_iterator =
	bksge::contiguous_iterator<It> &&
	detail::is_span_compatible_ref<T, bksge::iter_reference_t<It>>::value;

#else

template <typename It, typename T>
using span_compatible_iterator = bksge::conjunction<
	bksge::contiguous_iterator<It>,
	detail::is_span_compatible_ref<T, bksge::iter_reference_t<It>>
>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_SPAN_COMPATIBLE_ITERATOR_HPP
