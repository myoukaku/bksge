/**
 *	@file	negate.hpp
 *
 *	@brief	negate クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_NEGATE_HPP
#define BKSGE_FND_FUNCTIONAL_NEGATE_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::negate;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	符号反転を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct negate
{
	BKSGE_CONSTEXPR T operator()(T const& arg) const
	{
		return -arg;
	}
};

/**
 *	@brief	negate のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct negate<void>
{
	using is_transparent = void;

	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& arg) const
	-> decltype(-bksge::forward<T>(arg))
	{
		return -bksge::forward<T>(arg);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_NEGATE_HPP
