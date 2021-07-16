/**
 *	@file	sentinel_t.hpp
 *
 *	@brief	ranges::sentinel_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_SENTINEL_T_HPP
#define BKSGE_FND_RANGES_SENTINEL_T_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::range, Range)>
using sentinel_t = decltype(ranges::end(std::declval<Range&>()));

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_SENTINEL_T_HPP
