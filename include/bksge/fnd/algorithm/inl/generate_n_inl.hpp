/**
 *	@file	generate_n_inl.hpp
 *
 *	@brief	generate_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_GENERATE_N_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_GENERATE_N_INL_HPP

#include <bksge/fnd/algorithm/generate_n.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename OutputIterator,
	typename Size,
	typename Generator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
generate_n(OutputIterator first, Size n, Generator gen)
{
	while (n-- > 0)
	{
		*first++ = gen();
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_GENERATE_N_INL_HPP
