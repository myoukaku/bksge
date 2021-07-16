/**
 *	@file	reduce.hpp
 *
 *	@brief	reduce の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_REDUCE_HPP
#define BKSGE_FND_NUMERIC_REDUCE_HPP

#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '...' to '...', possible loss of data

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, bksge::false_type)
{
	for (; first != last; ++first)
	{
		init = binary_op(init, *first);
	}

	return init;
}

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, bksge::true_type)
{
	while ((last - first) >= 4)
	{
		T v1 = binary_op(first[0], first[1]);
		T v2 = binary_op(first[2], first[3]);
		T v3 = binary_op(v1, v2);
		init = binary_op(init, v3);
		first += 4;
	}

	return reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		bksge::false_type{});
}

BKSGE_WARNING_POP();

}	// namespace detail

template <typename InputIterator, typename T, typename BinaryOperation>
inline BKSGE_CXX14_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	using value_type = typename bksge::iterator_traits<InputIterator>::value_type;
	static_assert(bksge::is_invocable_r<T, BinaryOperation&, T&, T&>::value, "");
	static_assert(bksge::is_convertible<value_type, T>::value, "");

	return detail::reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		bksge::is_random_access_iterator<InputIterator>{});
}

template <typename InputIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init)
{
	return bksge::reduce(
		std::move(first),
		std::move(last),
		std::move(init),
		bksge::plus<>{});
}

template <typename InputIterator>
inline BKSGE_CXX14_CONSTEXPR typename bksge::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
	using value_type = typename bksge::iterator_traits<InputIterator>::value_type;
	return bksge::reduce(
		std::move(first),
		std::move(last),
		value_type{},
		bksge::plus<>{});
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_REDUCE_HPP
