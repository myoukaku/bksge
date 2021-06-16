/**
 *	@file	sample_inl.hpp
 *
 *	@brief	sample の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SAMPLE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SAMPLE_INL_HPP

#include <bksge/fnd/algorithm/sample.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/random/distributions/uniform_int_distribution.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator& g,
	bksge::input_iterator_tag*)
{
	using Distribution = bksge::uniform_int_distribution<Distance>;

	Distance k = 0;
	for (; first != last && k < n; ++first, ++k)
	{
		out[k] = *first;
	}

	auto const sz = k;
	for (; first != last; ++first, ++k)
	{
		auto const r = Distribution(0, k)(g);
		if (r < sz)
		{
			out[r] = *first;
		}
	}

	return out + bksge::min(n, k);
}

template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator& g,
	bksge::forward_iterator_tag*)
{
	using Distribution = bksge::uniform_int_distribution<Distance>;

	auto unsampled_sz = bksge::distance(first, last);
	for (n = bksge::min(n, unsampled_sz); n != 0; ++first)
	{
		auto const r = Distribution(0, --unsampled_sz)(g);

		if (r < n)
		{
			*out++ = *first;
			--n;
		}
	}

	return out;
}

}	// namespace detail

template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator,
	typename
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator&& g)
{
	using Category = bksge::iterator_category<PopulationIterator>*;
	using Difference = bksge::iter_difference_t<PopulationIterator>;
	using CommonType = bksge::common_type_t<Distance, Difference>;

	BKSGE_ASSERT(n >= 0);

	return bksge::algorithm::detail::sample(
		first,
		last,
		out,
		CommonType(n),
		g,
		Category());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SAMPLE_INL_HPP
