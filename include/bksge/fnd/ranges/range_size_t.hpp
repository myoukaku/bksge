/**
 *	@file	range_size_t.hpp
 *
 *	@brief	ranges::range_size_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_RANGE_SIZE_T_HPP
#define BKSGE_FND_RANGES_RANGE_SIZE_T_HPP

#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	ranges::sized_range Range
#else
	typename Range,
	typename = bksge::enable_if_t<ranges::sized_range<Range>::value>
#endif
>
using range_size_t = decltype(ranges::size(bksge::declval<Range&>()));

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_RANGE_SIZE_T_HPP
