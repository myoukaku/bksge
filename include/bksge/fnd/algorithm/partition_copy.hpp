/**
 *	@file	partition_copy.hpp
 *
 *	@brief	partition_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PARTITION_COPY_HPP
#define BKSGE_FND_ALGORITHM_PARTITION_COPY_HPP

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲を条件によって 2 つの出力の範囲へ分けてコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator1
 *	@tparam		OutputIterator2
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		out_true
 *	@param		out_false
 *	@param		pred
 *
 *	@require	InputIterator の value type は Assignable で、
 *				out_true と out_false の OutputIterator へ書き込み可能で、
 *				Predicate の argument type へ変換可能でなければならない。
 *				入力範囲は出力範囲のどちらとも重なっていてはならない。
 *
 *	@effect		[first,last) 内にあるそれぞれのイテレータ i について、
 *				pred(*i) が true なら *i を out_true へコピーし、
 *				そうでない場合は out_false へコピーする。
 *
 *	@return		first には out_true の終端が、
 *				second には out_false の終端が格納されたpairオブジェクトを返す。
 *
 *	@complexity	正確に last - first 回述語が適用される。
 */
template <
	typename InputIterator,
	typename OutputIterator1,
	typename OutputIterator2,
	typename Predicate
>
BKSGE_CXX14_CONSTEXPR bksge::pair<OutputIterator1, OutputIterator2>
partition_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator1 out_true,
	OutputIterator2 out_false,
	Predicate pred);

}	// namespace algorithm

using algorithm::partition_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/partition_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PARTITION_COPY_HPP
