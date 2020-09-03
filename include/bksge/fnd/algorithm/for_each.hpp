/**
 *	@file	for_each.hpp
 *
 *	@brief	for_each の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FOR_EACH_HPP
#define BKSGE_FND_ALGORITHM_FOR_EACH_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の全ての要素に、指定された関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		Function
 *
 *	@param		first
 *	@param		last
 *	@param		f
 *
 *	@require	Function は MoveConstructible の要件を満たす必要があるが、
 *				CopyConstructible の要件を満たす必要はない。
 *
 *	@effect		[first,last) 内の全てのイテレータ i に f(*i) という操作を行う。
 *				first から順番に処理し、last - 1 まで行う。
 *				このアルゴリズムはその他のアルゴリズムと違い、Function の内部で *i の値を書き換えても構わない
 *				（もちろんイテレータの型が mutable iterator の要件を満たしている場合に限る）。
 *
 *	@return		std::move(f)
 *
 *	@complexity	正確に f を last - first 回適用する
 *
 *	@note		f に戻り値がある場合、それは単に無視される。
 */
template <typename InputIterator, typename Function>
BKSGE_CXX14_CONSTEXPR Function
for_each(InputIterator first, InputIterator last, Function f);

}	// namespace algorithm

using algorithm::for_each;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/for_each_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FOR_EACH_HPP
