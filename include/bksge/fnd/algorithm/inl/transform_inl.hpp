/**
 *	@file	transform_inl.hpp
 *
 *	@brief	transform の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_TRANSFORM_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_TRANSFORM_INL_HPP

#include <bksge/fnd/algorithm/transform.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename UnaryOperation,
	typename
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	UnaryOperation unary_op)
{
	while (first != last)
	{
		*result++ = unary_op(*first++);
	}

	return result;
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename BinaryOperation,
	typename
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result,
	BinaryOperation binary_op)
{
	while (first1 != last1 && first2 != last2)
	{
		*result++ = binary_op(*first1++, *first2++);
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_TRANSFORM_INL_HPP
