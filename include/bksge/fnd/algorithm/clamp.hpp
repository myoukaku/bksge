/**
 *	@file	clamp.hpp
 *
 *	@brief	clamp の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_CLAMP_HPP
#define BKSGE_FND_ALGORITHM_CLAMP_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		値を最小値と最大値の範囲内に収める
 *
 *	@tparam		T		対象となる値の型
 *
 *	@param		v		対象となる値
 *	@param		lo		最小値
 *	@param		hi		最大値
 *
 *	@require	T は LessThanComparable でなければならない
 *
 *	@return		vがhiより小さければ、vとloの大きい方の値
 *				そうでなければ、     vとhiの小さい方の値
 *
 *	@complexity	最大で2回の比較
 */
template <typename T>
BKSGE_CONSTEXPR T const& clamp(T const& v, T const& lo, T const& hi);

/**
 *	@brief		値を最小値と最大値の範囲内に収める
 *
 *	@tparam		T		対象となる値の型
 *	@tparam		Compare	比較関数の型
 *
 *	@param		v		対象となる値
 *	@param		lo		最小値
 *	@param		hi		最大値
 *	@param		comp	比較関数
 *
 *	@return		vがhiより小さければ、vとloの大きい方の値
 *				そうでなければ、     vとhiの小さい方の値
 *
 *	@complexity	最大で2回の比較
 */
template <typename T, typename Compare>
BKSGE_CONSTEXPR T const& clamp(T const& v, T const& lo, T const& hi, Compare comp);

}	// namespace algorithm

using algorithm::clamp;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/clamp_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_CLAMP_HPP
