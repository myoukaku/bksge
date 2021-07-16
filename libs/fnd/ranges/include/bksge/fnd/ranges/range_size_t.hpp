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
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::sized_range, Range)>
using range_size_t = decltype(ranges::size(std::declval<Range&>()));

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_RANGE_SIZE_T_HPP
