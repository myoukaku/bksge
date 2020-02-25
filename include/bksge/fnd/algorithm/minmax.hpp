/**
 *	@file	minmax.hpp
 *
 *	@brief	minmax の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MINMAX_HPP
#define BKSGE_FND_ALGORITHM_MINMAX_HPP

#include <bksge/fnd/config.hpp>
#include <initializer_list>
#include <utility>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		同じ型の2つの値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	正確に1回の比較
 */
template <typename T>
BKSGE_CONSTEXPR std::pair<T const&, T const&>
minmax(T const& a, T const& b);

/**
 *	@brief		同じ型の2つの値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	正確に1回の述語適用
 */
template <typename T, typename Compare>
BKSGE_CONSTEXPR std::pair<T const&, T const&>
minmax(T const& a, T const& b, Compare comp);

/**
 *	@brief		initializer_listによるN個の値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *				要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	高々(3/2) * t.size()回の比較
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR std::pair<T, T>
minmax(std::initializer_list<T> t);

/**
 *	@brief		initializer_listによるN個の値のうち、最小値と最大値の組を取得する。
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
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	高々(3/2) * t.size()回の述語適用
 */
template <typename T, typename Compare>
BKSGE_CXX14_CONSTEXPR std::pair<T, T>
minmax(std::initializer_list<T> t, Compare comp);

}	// namespace algorithm

using algorithm::minmax;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/minmax_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MINMAX_HPP
