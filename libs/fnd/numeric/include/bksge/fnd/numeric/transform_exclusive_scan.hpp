/**
 *	@file	transform_exclusive_scan.hpp
 *
 *	@brief	transform_exclusive_scan の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define BKSGE_FND_NUMERIC_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename T,
	typename BinaryOperation,
	typename UnaryOperation
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
transform_exclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T init,
	BinaryOperation binary_op,
	UnaryOperation unary_op)
{
	while (first != last)
	{
		auto v = init;
		init = binary_op(init, unary_op(*first));
		++first;
		*result++ = std::move(v);
	}

	return result;
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_TRANSFORM_EXCLUSIVE_SCAN_HPP
