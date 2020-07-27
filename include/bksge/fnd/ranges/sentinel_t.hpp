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
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	ranges::range Range
#else
	typename Range,
	typename = bksge::enable_if_t<ranges::range<Range>::value>
#endif
>
using sentinel_t = decltype(ranges::end(bksge::declval<Range&>()));

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_SENTINEL_T_HPP
