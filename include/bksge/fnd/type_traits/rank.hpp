﻿/**
 *	@file	rank.hpp
 *
 *	@brief	rank の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_RANK_HPP
#define BKSGE_FND_TYPE_TRAITS_RANK_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	配列型の次元数を取得する。
 *
 *	@tparam		T
 *
 *	型Tが配列型である場合、配列の次元数となる整数値をメンバ定数valueの値として定義する。
 *	配列型でなければ0をメンバ定数valueの値として定義する。
 */
template <typename T>
struct rank
	: public detail::constant_wrapper<
		std::rank<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_RANK_HPP
