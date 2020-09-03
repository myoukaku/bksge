/**
 *	@file	mismatch_inl.hpp
 *
 *	@brief	mismatch の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MISMATCH_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MISMATCH_INL_HPP

#include <bksge/fnd/algorithm/mismatch.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator1, typename InputIterator2>
inline BKSGE_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2)
{
	return bksge::algorithm::mismatch(
		first1, last1, first2, bksge::equal_to<>());
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
inline BKSGE_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred)
{
	while (first1 != last1 && pred(*first1, *first2))
	{
		++first1, ++first2;
	}

	return std::make_pair(first1, first2);
}

template <typename InputIterator1, typename InputIterator2>
inline BKSGE_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2)
{
	return bksge::algorithm::mismatch(
		first1, last1, first2, last2, bksge::equal_to<>());
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
inline BKSGE_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	BinaryPredicate pred)
{
	while (first1 != last1 && first2 != last2 && pred(*first1, *first2))
	{
		++first1, ++first2;
	}

	return std::make_pair(first1, first2);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MISMATCH_INL_HPP
