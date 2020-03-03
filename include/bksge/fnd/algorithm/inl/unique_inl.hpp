/**
 *	@file	unique_inl.hpp
 *
 *	@brief	unique の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_UNIQUE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_UNIQUE_INL_HPP

#include <bksge/fnd/algorithm/unique.hpp>
#include <bksge/fnd/algorithm/adjacent_find.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
unique(ForwardIterator first, ForwardIterator last)
{
	return bksge::algorithm::unique(
		first, last, bksge::equal_to<>());
}

template <
	typename ForwardIterator,
	typename BinaryPredicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
unique(
	ForwardIterator first,
	ForwardIterator last,
	BinaryPredicate pred)
{
	using PredRef = bksge::add_lvalue_reference_t<BinaryPredicate>;

	first = bksge::adjacent_find<ForwardIterator, PredRef>(
		first, last, pred);

	if (first != last)
	{
		// ...  a  a  ?  ...
		//      f     i
		auto i = first;
		for (++i; ++i != last;)
		{
			if (!pred(*first, *i))
			{
				*++first = bksge::move(*i);
			}
		}

		++first;
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_UNIQUE_INL_HPP
