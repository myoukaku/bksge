/**
 *	@file	copy_if.hpp
 *
 *	@brief	copy_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COPY_IF_HPP
#define BKSGE_FND_ALGORITHM_COPY_IF_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された範囲の条件を満たす要素のみをコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *
 *	@require	[first,last) の範囲と、[result,result + (last - first)) の範囲は重なっていてはならない。
 *
 *	@return		コピー先の範囲の終端を返す。
 *
 *	@effect		[first,last) 内のイテレータ i について
 *				pred(*i) が true である要素を result へ順番にコピーする。
 *
 *	@complexity	正確に last - first 回述語を適用する。
 *
 *	@note		このコピーは安定なコピーである。つまり、コピーによって要素の前後が入れ替わることは無い。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate
>
OutputIterator
copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred);

}	// namespace algorithm

using algorithm::copy_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/copy_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COPY_IF_HPP
