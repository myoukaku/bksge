/**
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
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <typename InputIterator, typename OutputIterator>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
partial_sum(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return bksge::partial_sum(
		std::move(first),
		std::move(last),
		std::move(result),
		bksge::plus<>());
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
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
		sum = binary_op(std::move(sum), *first);
		*++result = sum;
	}
	
	return ++result;
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_PARTIAL_SUM_INL_HPP
