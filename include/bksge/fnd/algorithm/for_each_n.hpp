/**
 *	@file	for_each_n.hpp
 *
 *	@brief	for_each_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FOR_EACH_N_HPP
#define BKSGE_FND_ALGORITHM_FOR_EACH_N_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の全ての要素に、指定された関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		Size
 *	@tparam		Function
 *
 *	@param		first	関数を適用する範囲の初め
 *	@param		n		関数を適用する要素の数
 *	@param		f		適用する関数
 *
 *	@require	InputIterator は InputIterator の要件を満たす必要がある
 *				Function は MoveConstructible の要件を満たす必要があるが、
 *				CopyConstructible の要件を満たす必要はない。
 *
 *	@effect		[first, first + n) 内の全てのイテレータ i に
 *				先頭から順番に f(*i) という操作を行う。
 *				このアルゴリズムはその他のアルゴリズムと違い、Function の内部で *i の値を書き換えても構わない
 *				（もちろんイテレータの型が mutable iterator の要件を満たしている場合に限る）。
 *
 *	@return		first + n
 *
 *	@complexity	正確に f を n 回適用する
 *
 *	@note		f に戻り値がある場合、それは単に無視される。
 */
template <
	typename InputIterator,
	typename Size,
	typename Function,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR InputIterator
for_each_n(InputIterator first, Size n, Function f);

}	// namespace algorithm

using algorithm::for_each_n;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/for_each_n_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FOR_EACH_N_HPP
