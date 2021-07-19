/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP
#define BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::bit_not;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <utility>

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
	->decltype(~std::forward<T>(arg))
	{
		return ~std::forward<T>(arg);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_BIT_NOT_HPP
