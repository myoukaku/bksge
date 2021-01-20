/**
 *	@file	less_equal.hpp
 *
 *	@brief	less_equal クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LESS_EQUAL_HPP
#define BKSGE_FND_FUNCTIONAL_LESS_EQUAL_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::less_equal;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	左辺が右辺以下かの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct less_equal
{
	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs <= rhs;
	}
};

/**
 *	@brief	less_equal のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct less_equal<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(bksge::forward<T>(lhs) <= bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) <= bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_LESS_EQUAL_HPP
