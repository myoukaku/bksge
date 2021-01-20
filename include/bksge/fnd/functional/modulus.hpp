/**
 *	@file	modulus.hpp
 *
 *	@brief	modulus クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_MODULUS_HPP
#define BKSGE_FND_FUNCTIONAL_MODULUS_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::modulus;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

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

#endif

#endif // BKSGE_FND_FUNCTIONAL_MODULUS_HPP
