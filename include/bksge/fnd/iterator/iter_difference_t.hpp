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
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <iterator>

namespace bksge
{

namespace detail
{

template <typename T, typename = bksge::void_t<>>
struct iter_difference_impl
{
	using type = typename bksge::incrementable_traits<T>::difference_type;
};
 
template <typename T>
struct iter_difference_impl<T, bksge::void_t<typename std::iterator_traits<T>::difference_type>>
{
	using type = typename std::iterator_traits<T>::difference_type;
};

}	// namespace detail

template <typename T>
using iter_difference_t =
	typename detail::iter_difference_impl<bksge::remove_cvref_t<T>>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_DIFFERENCE_T_HPP
