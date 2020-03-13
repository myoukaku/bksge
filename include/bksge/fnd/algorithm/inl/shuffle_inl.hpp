/**
 *	@file	shuffle_inl.hpp
 *
 *	@brief	shuffle の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SHUFFLE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SHUFFLE_INL_HPP

#include <bksge/fnd/algorithm/shuffle.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
//#include <bksge/fnd/random/uniform_int_distribution.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <cstddef>
#include <random>

namespace bksge
{

namespace algorithm
{

template <
	typename RandomAccessIterator,
	typename UniformRandomNumberGenerator,
	typename
>
inline void
shuffle(
	RandomAccessIterator first,
	RandomAccessIterator last,
	UniformRandomNumberGenerator&& g)
{
	using difference_type = bksge::iterator_difference_type<RandomAccessIterator>;
	using D = std::uniform_int_distribution<std::ptrdiff_t>;
	using P = typename D::param_type;
	
	auto d = last - first;

	if (d > 1)
	{
		D uid;

		for (--last, --d; first < last; ++first, --d)
		{
			auto i = uid(g, P(0, d));

			if (i != difference_type(0))
			{
				swap(*first, *(first + i));
			}
		}
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SHUFFLE_INL_HPP
