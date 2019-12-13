/**
 *	@file	logical_not.hpp
 *
 *	@brief	logical_not クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP
#define BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	論理否定(NOT)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_not
{
	using result_type   = bool;
	using argument_type = T;

	BKSGE_CONSTEXPR T operator()(T const& arg) const
	{
		return !arg;
	}
};

/**
 *	@brief	logical_not のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_not<void>
{
	using is_transparent = void;

	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& arg) const
	-> decltype(!bksge::forward<T>(arg))
	{
		return !bksge::forward<T>(arg);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP
