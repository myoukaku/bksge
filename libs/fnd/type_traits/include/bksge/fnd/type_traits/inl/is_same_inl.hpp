/**
 *	@file	is_same_inl.hpp
 *
 *	@brief	is_same の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_SAME_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_SAME_INL_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

template <typename T, typename U>
struct is_same : public bksge::false_type {};

template <typename T>
struct is_same<T, T> : public bksge::true_type {};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_SAME_INL_HPP
