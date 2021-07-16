/**
 *	@file	inclusive_scan.hpp
 *
 *	@brief	inclusive_scan の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INCLUSIVE_SCAN_HPP
#define BKSGE_FND_NUMERIC_INCLUSIVE_SCAN_HPP

#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
inclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op,
	T init)
{
	for (; first != last; ++first)
	{
		*result++ = init = binary_op(init, *first);
	}

	return result;
}

template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
inclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op)
{
	if (first != last)
	{
		auto init = *first;
		*result++ = init;
		++first;
		if (first != last)
		{
			result = bksge::inclusive_scan(
				first, last, result, binary_op, std::move(init));
		}
	}

	return result;
}

template <typename InputIterator, typename OutputIterator>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
inclusive_scan(InputIterator first, InputIterator last, OutputIterator result)
{
	return bksge::inclusive_scan(first, last, result, bksge::plus<>{});
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INCLUSIVE_SCAN_HPP
