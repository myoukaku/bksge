/**
 *	@file	upper_bound_inl.hpp
 *
 *	@brief	upper_bound の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP

#include <bksge/fnd/algorithm/upper_bound.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	auto len = bksge::distance(first, last);

	while (len != 0)
	{
		auto l2 = len / 2;
		auto m = first;
		bksge::advance(m, l2);

		if (comp(value, *m))
		{
			len = l2;
		}
		else
		{
			first = ++m;
			len -= l2 + 1;
		}
	}

	return first;
}

}	// namespace detail

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return bksge::algorithm::upper_bound(
		first, last, value, bksge::less<>());
}

template <
	typename ForwardIterator,
	typename T,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::upper_bound<CompRef>(first, last, value, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_UPPER_BOUND_INL_HPP
