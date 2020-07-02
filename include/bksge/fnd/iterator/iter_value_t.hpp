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
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/iterator/indirectly_readable_traits.hpp>
#include <iterator>

namespace bksge
{

namespace detail
{

template <typename T, typename = bksge::void_t<>>
struct iter_value_impl
{
	using type = typename bksge::indirectly_readable_traits<T>::value_type;
};
 
template <typename T>
struct iter_value_impl<T, bksge::void_t<typename std::iterator_traits<T>::value_type>>
{
	using type = typename std::iterator_traits<T>::value_type;
};

}	// namespace detail

template <typename T>
using iter_value_t =
	typename detail::iter_value_impl<bksge::remove_cvref_t<T>>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_VALUE_T_HPP
