/**
 *	@file	transform_inclusive_scan.hpp
 *
 *	@brief	transform_inclusive_scan の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_TRANSFORM_INCLUSIVE_SCAN_HPP
#define BKSGE_FND_NUMERIC_TRANSFORM_INCLUSIVE_SCAN_HPP

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation,
	typename UnaryOperation,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
transform_inclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op,
	UnaryOperation unary_op,
	T init)
{
	for (; first != last; ++first)
	{
		*result++ = init = binary_op(init, unary_op(*first));
	}

	return result;
}

template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation,
	typename UnaryOperation
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
transform_inclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op,
	UnaryOperation unary_op)
{
	if (first != last)
	{
		auto init = unary_op(*first);
		*result++ = init;
		++first;

		if (first != last)
		{
			result = bksge::transform_inclusive_scan(
				first,
				last,
				result,
				binary_op,
				unary_op,
				std::move(init));
		}
	}

	return result;
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_TRANSFORM_INCLUSIVE_SCAN_HPP
