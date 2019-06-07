/**
 *	@file	max.hpp
 *
 *	@brief	max の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_ALGORITHM_MAX_HPP
#define BKSGE_ALGORITHM_MAX_HPP

#include <bksge/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		同じ型の2つの値のうち、最大値を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *
 *	@return		最大値
 *
 *	@complexity	正確に1回の比較
 */
template <typename T>
BKSGE_CONSTEXPR T const&
max(T const& a, T const& b);

/**
 *	@brief		同じ型の2つの値のうち、最大値を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@return		最大値
 *
 *	@complexity	正確に1回の述語適用
 */
template <typename T, typename Compare>
BKSGE_CONSTEXPR T const&
max(T const& a, T const& b, Compare comp);

}	// namespace algorithm

using algorithm::max;

}	// namespace bksge

#include <bksge/algorithm/inl/max_inl.hpp>

#endif // BKSGE_ALGORITHM_MAX_HPP
