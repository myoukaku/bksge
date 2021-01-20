/**
 *	@file	logical_and.hpp
 *
 *	@brief	logical_and クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LOGICAL_AND_HPP
#define BKSGE_FND_FUNCTIONAL_LOGICAL_AND_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::logical_and;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	論理積(AND)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_and
{
	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs && rhs;
	}
};

/**
 *	@brief	logical_and のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_and<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) && bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) && bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_LOGICAL_AND_HPP
