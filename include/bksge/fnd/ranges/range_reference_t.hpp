/**
 *	@file	range_reference_t.hpp
 *
 *	@brief	ranges::range_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_RANGE_REFERENCE_T_HPP
#define BKSGE_FND_RANGES_RANGE_REFERENCE_T_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::range, Range)>
using range_reference_t = bksge::iter_reference_t<ranges::iterator_t<Range>>;

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_RANGE_REFERENCE_T_HPP
