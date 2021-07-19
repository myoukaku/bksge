/**
 *	@file	plus.hpp
 *
 *	@brief	plus クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_PLUS_HPP
#define BKSGE_FND_FUNCTIONAL_PLUS_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::plus;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

/**
 *	@brief	加算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct plus
{
	BKSGE_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
	{
		return lhs + rhs;
	}
};

/**
 *	@brief	plus のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct plus<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(std::forward<T>(lhs) + std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) + std::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_PLUS_HPP
