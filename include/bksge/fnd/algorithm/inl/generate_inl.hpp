/**
 *	@file	generate_inl.hpp
 *
 *	@brief	generate の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_GENERATE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_GENERATE_INL_HPP

#include <bksge/fnd/algorithm/generate.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename Generator>
inline BKSGE_CXX14_CONSTEXPR void
generate(ForwardIterator first, ForwardIterator last, Generator gen)
{
	while (first != last)
	{
		*first++ = gen();
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_GENERATE_INL_HPP
