/**
 *	@file	clamp_iter_cat.hpp
 *
 *	@brief	clamp_iter_cat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_DETAIL_CLAMP_ITER_CAT_HPP
#define BKSGE_FND_ITERATOR_DETAIL_CLAMP_ITER_CAT_HPP

#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>

namespace bksge
{

namespace detail
{

// Weaken iterator_category Cat to Limit if it is derived from that,
// otherwise use Otherwise.
template <typename Cat, typename Limit, typename Otherwise = Cat>
using clamp_iter_cat =
	bksge::conditional_t<bksge::is_derived_from<Cat, Limit>::value, Limit, Otherwise>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_DETAIL_CLAMP_ITER_CAT_HPP
