/**
 *	@file	unreachable_sentinel.hpp
 *
 *	@brief	unreachable_sentinel の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_UNREACHABLE_SENTINEL_HPP
#define BKSGE_FND_ITERATOR_UNREACHABLE_SENTINEL_HPP

#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

struct unreachable_sentinel_t
{
	template <BKSGE_REQUIRES_PARAM(bksge::weakly_incrementable, It)>
	friend BKSGE_CONSTEXPR bool
	operator==(unreachable_sentinel_t, It const&) BKSGE_NOEXCEPT
	{
		return false;
	}
};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
unreachable_sentinel_t unreachable_sentinel{};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_UNREACHABLE_SENTINEL_HPP
