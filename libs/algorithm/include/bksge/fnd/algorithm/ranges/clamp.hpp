/**
 *	@file	clamp.hpp
 *
 *	@brief	ranges::clamp の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_CLAMP_HPP
#define BKSGE_FND_ALGORITHM_RANGES_CLAMP_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace ranges
{

struct clamp_fn
{
	template <
		typename T,
		typename Proj = bksge::identity,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::indirect_strict_weak_order<
			bksge::projected<T const*, Proj>
		> Comp = ranges::less
#else
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<T const*, Proj>
			>::value
		>
#endif
	>
	BKSGE_CXX14_CONSTEXPR T const&
	operator()(T const& val, T const& lo, T const& hi,
		Comp comp = {}, Proj proj = {}) const
	{
		BKSGE_ASSERT(!(bksge::invoke(comp,
			bksge::invoke(proj, hi),
			bksge::invoke(proj, lo))));

		auto&& proj_val = bksge::invoke(proj, val);

		return
			bksge::invoke(comp, proj_val, bksge::invoke(proj, lo)) ?
				lo :
			bksge::invoke(comp, bksge::invoke(proj, hi), proj_val) ?
				hi :
			val;
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR clamp_fn clamp{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_CLAMP_HPP
