/**
 *	@file	exclusive_scan.hpp
 *
 *	@brief	exclusive_scan の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_EXCLUSIVE_SCAN_HPP
#define BKSGE_FND_NUMERIC_EXCLUSIVE_SCAN_HPP

#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename T,
	typename BinaryOperation
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
exclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T init,
	BinaryOperation binary_op)
{
	while (first != last)
	{
		auto v = init;
		init = binary_op(init, *first);
		++first;
		*result++ = bksge::move(v);
	}

	return result;
}

template <typename InputIterator, typename OutputIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
exclusive_scan(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T init)
{
	return bksge::exclusive_scan(
		first,
		last,
		result,
		bksge::move(init),
		bksge::plus<>{});
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_EXCLUSIVE_SCAN_HPP
