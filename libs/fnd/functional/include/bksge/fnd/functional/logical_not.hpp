/**
 *	@file	logical_not.hpp
 *
 *	@brief	logical_not クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP
#define BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::logical_not;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <utility>

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
	->decltype(!std::forward<T>(arg))
	{
		return !std::forward<T>(arg);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_LOGICAL_NOT_HPP
