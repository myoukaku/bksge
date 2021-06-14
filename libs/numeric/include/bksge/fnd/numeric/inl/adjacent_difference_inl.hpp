/**
 *	@file	adjacent_difference_inl.hpp
 *
 *	@brief	adjacent_difference の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INL_ADJACENT_DIFFERENCE_INL_HPP
#define BKSGE_FND_NUMERIC_INL_ADJACENT_DIFFERENCE_INL_HPP

#include <bksge/fnd/numeric/adjacent_difference.hpp>
#include <bksge/fnd/functional/minus.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename InputIterator, typename OutputIterator>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return bksge::adjacent_difference(
		bksge::move(first),
		bksge::move(last),
		bksge::move(result),
		bksge::minus<>());
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op)
{
	if (first == last)
	{
		return result;
	}

	auto acc = *first;
	*result = acc;
	++result;
	++first;

	while (first != last)
	{
		auto val = *first;
		*result = binary_op(val, bksge::move(acc));
		acc = bksge::move(val);

		++result;
		++first;
	}

	return result;
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_ADJACENT_DIFFERENCE_INL_HPP
