﻿/**
 *	@file	nth.hpp
 *
 *	@brief	nth の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_NTH_HPP
#define BKSGE_FND_TYPE_TRAITS_NTH_HPP

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

/**
 *	@brief		テンプレートパラメータパックのN番目の型を得る
 *
 *	@tparam		N
 *	@tparam		Types
 */
template <bksge::size_t N, typename... Types>
struct nth;

/**
 *	@brief	nthのエイリアステンプレート
 */
template <bksge::size_t N, typename... Types>
using nth_t = typename nth<N, Types...>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/nth_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_NTH_HPP
