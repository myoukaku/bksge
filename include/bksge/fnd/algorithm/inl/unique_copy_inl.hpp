/**
 *	@file	unique_copy_inl.hpp
 *
 *	@brief	unique_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_UNIQUE_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_UNIQUE_COPY_INL_HPP

#include <bksge/fnd/algorithm/unique_copy.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename InputIterator,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryPredicate pred,
	std::input_iterator_tag*,
	std::output_iterator_tag*)
{
	if (first != last)
	{
		bksge::iter_value_t<InputIterator> t(*first);
		*result = t;
		++result;

		while (++first != last)
		{
			if (!pred(t, *first))
			{
				t = *first;
				*result = t;
				++result;
			}
		}
	}

	return result;
}

template <
	typename BinaryPredicate,
	typename ForwardIterator,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(
	ForwardIterator first,
	ForwardIterator last,
	OutputIterator result,
	BinaryPredicate pred,
	std::forward_iterator_tag*,
	std::output_iterator_tag*)
{
	if (first != last)
	{
		auto i = first;
		*result = *i;
		++result;

		while (++first != last)
		{
			if (!pred(*i, *first))
			{
				*result = *first;
				++result;
				i = first;
			}
		}
	}

	return result;
}

template <
	typename BinaryPredicate,
	typename InputIterator,
	typename ForwardIterator
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
unique_copy(
	InputIterator first,
	InputIterator last,
	ForwardIterator result,
	BinaryPredicate pred,
	std::input_iterator_tag*,
	std::forward_iterator_tag*)
{
	if (first != last)
	{
		*result = *first;

		while (++first != last)
		{
			if (!pred(*result, *first))
			{
				*++result = *first;
			}
		}

		++result;
	}

	return result;
}

}	// namespace detail

template <
	typename InputIterator,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return bksge::algorithm::unique_copy(
		first, last, result, bksge::equal_to<>());
}

template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryPredicate pred)
{
	using Category1 = bksge::iterator_category<InputIterator>*;
	using Category2 = bksge::iterator_category<OutputIterator>*;
	return detail::unique_copy<bksge::add_lvalue_reference_t<BinaryPredicate>>(
		first, last, result, pred, Category1(), Category2());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_UNIQUE_COPY_INL_HPP
