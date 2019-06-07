/**
 *	@file	modulus.hpp
 *
 *	@brief	modulus クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_MODULUS_HPP
#define BKSGE_FUNCTIONAL_MODULUS_HPP

#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>

namespace bksge
{

/**
 *	@brief	剰余算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct modulus
{
	using result_type          = T;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
	{
		return lhs % rhs;
	}
};

/**
 *	@brief	modulus のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct modulus<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) % bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) % bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FUNCTIONAL_MODULUS_HPP
