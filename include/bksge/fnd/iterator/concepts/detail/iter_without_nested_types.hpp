/**
 *	@file	iter_without_nested_types.hpp
 *
 *	@brief	iter_without_nested_types の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP

#include <bksge/fnd/iterator/concepts/detail/iter_with_nested_types.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept iter_without_nested_types = !iter_with_nested_types<Iter>;

#else

template <typename Iter>
using iter_without_nested_types = bksge::negation<iter_with_nested_types<Iter>>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP
