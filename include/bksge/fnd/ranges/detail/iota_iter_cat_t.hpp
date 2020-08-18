/**
 *	@file	iota_iter_cat_t.hpp
 *
 *	@brief	iota_iter_cat_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_IOTA_ITER_CAT_T_HPP
#define BKSGE_FND_RANGES_DETAIL_IOTA_ITER_CAT_T_HPP

#include <bksge/fnd/ranges/detail/advanceable.hpp>
#include <bksge/fnd/ranges/detail/decrementable.hpp>
#include <bksge/fnd/iterator/concepts/incrementable.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/iterator/tag.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename T>
using iota_iter_cat_t =
	bksge::conditional_t<detail::is_advanceable<T>::value,   bksge::random_access_iterator_tag,
	bksge::conditional_t<detail::is_decrementable<T>::value, bksge::bidirectional_iterator_tag,
	bksge::conditional_t<bksge::is_incrementable<T>::value,  bksge::forward_iterator_tag,
				                                             bksge::input_iterator_tag
>>>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_IOTA_ITER_CAT_T_HPP
