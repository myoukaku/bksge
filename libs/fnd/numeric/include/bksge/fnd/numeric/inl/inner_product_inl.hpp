/**
 *	@file	inner_product_inl.hpp
 *
 *	@brief	inner_product の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INL_INNER_PRODUCT_INL_HPP
#define BKSGE_FND_NUMERIC_INL_INNER_PRODUCT_INL_HPP

#include <bksge/fnd/numeric/inner_product.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

template <
	typename InputIterator1,
	typename InputIterator2,
	typename T,
	typename BinaryOperation1,
	typename BinaryOperation2
>
inline BKSGE_CXX14_CONSTEXPR T
inner_product(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2)
{
	while (first1 != last1)
	{
		init = binary_op1(std::move(init), binary_op2(*first1, *first2));
		++first1;
		++first2;
	}

	return init;
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR T
inner_product(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	T init)
{
	return bksge::inner_product(
		std::move(first1),
		std::move(last1),
		std::move(first2),
		std::move(init),
		bksge::plus<>(),
		bksge::multiplies<>());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename T,
	typename BinaryOperation1,
	typename BinaryOperation2
>
inline BKSGE_CXX14_CONSTEXPR T
inner_product(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2)
{
	return detail::inner_product(
		std::move(first1),
		std::move(last1),
		std::move(first2),
		std::move(init),
		std::move(binary_op1),
		std::move(binary_op2));
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_INNER_PRODUCT_INL_HPP
