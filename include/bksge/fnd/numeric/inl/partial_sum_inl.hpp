﻿/**
 *	@file	partial_sum_inl.hpp
 *
 *	@brief	partial_sum の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INL_PARTIAL_SUM_INL_HPP
#define BKSGE_FND_NUMERIC_INL_PARTIAL_SUM_INL_HPP

#include <bksge/fnd/numeric/partial_sum.hpp>
#include <bksge/fnd/functional/plus.hpp>

namespace bksge
{

namespace numeric
{

template <typename InputIterator, typename OutputIterator, typename>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
partial_sum(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return bksge::numeric::partial_sum(first, last, result, bksge::plus<>());
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation, typename>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
partial_sum(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op)
{
	if (first == last)
	{
		return result;
	}

	auto sum = *first;
	*result = sum;
	
	while (++first != last)
	{
		sum = binary_op(sum, *first);
		*++result = sum;
	}
	
	return ++result;
}

}	// namespace numeric

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_PARTIAL_SUM_INL_HPP