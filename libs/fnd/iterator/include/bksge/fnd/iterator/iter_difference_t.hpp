/**
 *	@file	iter_difference_t.hpp
 *
 *	@brief	iter_difference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_DIFFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_DIFFERENCE_T_HPP

#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_traits.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using iter_diff_t_impl =
	typename detail::iter_traits<T, bksge::incrementable_traits<T>>::difference_type;

}	// namespace detail

template <typename T>
using iter_difference_t = detail::iter_diff_t_impl<bksge::remove_cvref_t<T>>;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_DIFFERENCE_T_HPP
