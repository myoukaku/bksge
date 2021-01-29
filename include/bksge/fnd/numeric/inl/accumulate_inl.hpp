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
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
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
		init = binary_op(bksge::move(init), *first++);
	}

	return init;
}

}	// namespace detail

template <typename InputIterator, typename T>
inline BKSGE_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init)
{
	return bksge::accumulate(
		bksge::move(first),
		bksge::move(last),
		bksge::move(init),
		bksge::plus<>());
}

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	return detail::accumulate(
		bksge::move(first),
		bksge::move(last),
		bksge::move(init),
		bksge::move(binary_op));
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_ACCUMULATE_INL_HPP
