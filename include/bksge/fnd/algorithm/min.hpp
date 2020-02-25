/**
 *	@file	min.hpp
 *
 *	@brief	min の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MIN_HPP
#define BKSGE_FND_ALGORITHM_MIN_HPP

#include <bksge/fnd/config.hpp>
#include <initializer_list>

namespace bksge
{

/**
 *	@brief		同じ型の2つの値のうち、最小値を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に1回の比較
 */
template <typename T>
BKSGE_CONSTEXPR T const&
min(T const& a, T const& b);

/**
 *	@brief		同じ型の2つの値のうち、最小値を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@return		最小値
 *
 *	@complexity	正確に1回の述語適用
 */
template <typename T, typename Compare>
BKSGE_CONSTEXPR T const&
min(T const& a, T const& b, Compare comp);

/**
 *	@brief		initializer_listによるN個の値のうち、最小値を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *				要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に t.size() - 1 回の比較
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR T
min(std::initializer_list<T> t);

/**
 *	@brief		initializer_listによるN個の値のうち、最小値を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@require	要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に t.size() - 1 回の述語適用
 */
template <typename T, typename Compare>
BKSGE_CXX14_CONSTEXPR T
min(std::initializer_list<T> t, Compare comp);

}	// namespace algorithm

#include <bksge/fnd/algorithm/inl/min_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MIN_HPP
