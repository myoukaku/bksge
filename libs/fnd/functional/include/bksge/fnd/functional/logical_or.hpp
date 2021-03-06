﻿/**
 *	@file	logical_or.hpp
 *
 *	@brief	logical_or クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LOGICAL_OR_HPP
#define BKSGE_FND_FUNCTIONAL_LOGICAL_OR_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::logical_or;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	論理和(OR)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_or
{
	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs || rhs;
	}
};

/**
 *	@brief	logical_or のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_or<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) || bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) || bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_LOGICAL_OR_HPP
