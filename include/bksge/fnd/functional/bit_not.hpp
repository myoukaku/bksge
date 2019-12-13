/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP
#define BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ビットごとの論理否定(NOT)をとる関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct bit_not
{
	using result_type   = T;
	using argument_type = T;

	BKSGE_CONSTEXPR T operator()(T const& arg) const
	{
		return ~arg;
	}
};

/**
 *	@brief	bit_not のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct bit_not<void>
{
	using is_transparent = void;

	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& arg) const
	-> decltype(~bksge::forward<T>(arg))
	{
		return ~bksge::forward<T>(arg);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP
