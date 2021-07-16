/**
 *	@file	transform_reduce.hpp
 *
 *	@brief	transform_reduce の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_TRANSFORM_REDUCE_HPP
#define BKSGE_FND_NUMERIC_TRANSFORM_REDUCE_HPP

#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '...' to '...', possible loss of data

template <
	typename InputIterator1, typename InputIterator2, typename T,
	typename BinaryOperation1, typename BinaryOperation2
>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce_impl(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2,
	bksge::false_type)
{
	for (; first1 != last1; ++first1, (void)++first2)
	{
		init = binary_op1(init, binary_op2(*first1, *first2));
	}

	return init;
}

template <
	typename InputIterator1, typename InputIterator2, typename T,
	typename BinaryOperation1, typename BinaryOperation2
>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce_impl(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2,
	bksge::true_type)
{
	while ((last1 - first1) >= 4)
	{
		T v1 = binary_op1(binary_op2(first1[0], first2[0]), binary_op2(first1[1], first2[1]));
		T v2 = binary_op1(binary_op2(first1[2], first2[2]), binary_op2(first1[3], first2[3]));
		T v3 = binary_op1(v1, v2);
		init = binary_op1(init, v3);
		first1 += 4;
		first2 += 4;
	}

	return transform_reduce_impl(
		std::move(first1),
		std::move(last1),
		std::move(first2),
		std::move(init),
		std::move(binary_op1),
		std::move(binary_op2),
		bksge::false_type{});
}

template <typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce_impl(
	InputIterator first, InputIterator last,
	T init,
	BinaryOperation binary_op,
	UnaryOperation unary_op,
	bksge::false_type)
{
	for (; first != last; ++first)
	{
		init = binary_op(init, unary_op(*first));
	}

	return init;
}

template <typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce_impl(
	InputIterator first, InputIterator last,
	T init,
	BinaryOperation binary_op,
	UnaryOperation unary_op,
	bksge::true_type)
{
	while ((last - first) >= 4)
	{
		T v1 = binary_op(unary_op(first[0]), unary_op(first[1]));
		T v2 = binary_op(unary_op(first[2]), unary_op(first[3]));
		T v3 = binary_op(v1, v2);
		init = binary_op(init, v3);
		first += 4;
	}

	return transform_reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		std::move(unary_op),
		bksge::false_type{});
}

BKSGE_WARNING_POP();

}	// namespace detail

template <
	typename InputIterator1, typename InputIterator2, typename T,
	typename BinaryOperation1, typename BinaryOperation2
>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2)
{
	return detail::transform_reduce_impl(
		std::move(first1),
		std::move(last1),
		std::move(first2),
		std::move(init),
		std::move(binary_op1),
		std::move(binary_op2),
		bksge::conjunction<
			bksge::is_random_access_iterator<InputIterator1>,
			bksge::is_random_access_iterator<InputIterator2>>{});
}

template <typename InputIterator1, typename InputIterator2, typename T>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	T init)
{
	return bksge::transform_reduce(
		std::move(first1),
		std::move(last1),
		std::move(first2),
		std::move(init),
		bksge::plus<>{},
		bksge::multiplies<>{});
}

template <typename InputIterator, typename T, typename BinaryOperation, typename UnaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
transform_reduce(
	InputIterator first, InputIterator last,
	T init,
	BinaryOperation binary_op,
	UnaryOperation unary_op)
{
	return detail::transform_reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		std::move(unary_op),
		bksge::is_random_access_iterator<InputIterator>{});
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_TRANSFORM_REDUCE_HPP
