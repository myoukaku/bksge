/**
 *	@file	count_if.hpp
 *
 *	@brief	count_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COUNT_IF_HPP
#define BKSGE_FND_ALGORITHM_COUNT_IF_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		条件を満たしている要素の数を数える
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) != false であるイテレータの数を返す
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 */
template <
	typename InputIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR iterator_difference_type<InputIterator>
count_if(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::count_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/count_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COUNT_IF_HPP
