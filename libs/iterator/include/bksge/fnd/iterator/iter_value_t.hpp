/**
 *	@file	iter_value_t.hpp
 *
 *	@brief	iter_value_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_VALUE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_VALUE_T_HPP

#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/iterator/indirectly_readable_traits.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_traits.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using iter_value_t_impl =
	typename detail::iter_traits<T, bksge::indirectly_readable_traits<T>>::value_type;

}	// namespace detail

template <typename T>
using iter_value_t = detail::iter_value_t_impl<bksge::remove_cvref_t<T>>;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_VALUE_T_HPP
