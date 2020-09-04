/**
 *	@file	equal_range_inl.hpp
 *
 *	@brief	equal_range の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_EQUAL_RANGE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_EQUAL_RANGE_INL_HPP

#include <bksge/fnd/algorithm/equal_range.hpp>
#include <bksge/fnd/algorithm/lower_bound.hpp>
#include <bksge/fnd/algorithm/upper_bound.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR
std::pair<ForwardIterator, ForwardIterator>
equal_range(
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

		if (comp(*m, value))
		{
			first = ++m;
			len -= l2 + 1;
		}
		else if (comp(value, *m))
		{
			last = m;
			len = l2;
		}
		else
		{
			auto mp1 = m;
			return std::make_pair(
				detail::lower_bound(first, m, value, comp),
				detail::upper_bound(++mp1, last, value, comp));
		}
	}

	return std::make_pair(first, first);
}

}	// namespace detail

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR
std::pair<ForwardIterator, ForwardIterator>
equal_range(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return bksge::algorithm::equal_range(
		first, last, value, bksge::less<>());
}

template <typename ForwardIterator, typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR
std::pair<ForwardIterator, ForwardIterator>
equal_range(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::equal_range<CompRef>(first, last, value, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_EQUAL_RANGE_INL_HPP
