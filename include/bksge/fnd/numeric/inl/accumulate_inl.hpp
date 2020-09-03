/**
 *	@file	accumulate_inl.hpp
 *
 *	@brief	accumulate の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INL_ACCUMULATE_INL_HPP
#define BKSGE_FND_NUMERIC_INL_ACCUMULATE_INL_HPP

#include <bksge/fnd/numeric/accumulate.hpp>
#include <bksge/fnd/functional/plus.hpp>

namespace bksge
{

namespace numeric
{

namespace detail
{

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
accumulate(
	InputIterator first,
	InputIterator last,
	T init,
	BinaryOperation binary_op)
{
	while (first != last)
	{
		init = binary_op(init, *first++);
	}

	return init;
}

}	// namespace detail

template <typename InputIterator, typename T>
inline BKSGE_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init)
{
	return bksge::numeric::accumulate(first, last, init, bksge::plus<>());
}

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	return detail::accumulate(first, last, init, binary_op);
}

}	// namespace numeric

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_ACCUMULATE_INL_HPP
