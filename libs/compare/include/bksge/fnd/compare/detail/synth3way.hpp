/**
 *	@file	synth3way.hpp
 *
 *	@brief	synth3way の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_SYNTH3WAY_HPP
#define BKSGE_FND_COMPARE_DETAIL_SYNTH3WAY_HPP

#include <bksge/fnd/compare/concepts/three_way_comparable_with.hpp>
#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/concepts/detail/boolean_testable.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

struct Synth3way
{
private:
	template <typename T, typename U>
	static BKSGE_CONSTEXPR bool
	s_noexcept(T const* t = nullptr, U const* u = nullptr)
	{
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		if constexpr (bksge::three_way_comparable_with<T, U>)
		{
			return noexcept(*t <=> *u);
		}
		else
#endif
		{
			return noexcept(*t < *u) && noexcept(*u < *t);
		}
	}

public:
	template <typename T, typename U>
	BKSGE_CXX14_CONSTEXPR auto
	operator()(T const& t, U const& u) const
		BKSGE_NOEXCEPT_IF((s_noexcept<T, U>()))
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		requires requires
		{
			{ t < u } -> bksge::detail::boolean_testable;
			{ u < t } -> bksge::detail::boolean_testable;
		}
#endif
	{
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		if constexpr (bksge::three_way_comparable_with<T, U>)
		{
			return t <=> u;
		}
		else
#endif
		{
			if (t < u)
			{
				return bksge::weak_ordering::less;
			}
			else if (u < t)
			{
				return bksge::weak_ordering::greater;
			}
			else
			{
				return bksge::weak_ordering::equivalent;
			}
		}
	}
};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
Synth3way synth3way = {};

template <typename T, typename U = T>
using synth3way_t = decltype(detail::synth3way(bksge::declval<T&>(), bksge::declval<U&>()));

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_SYNTH3WAY_HPP
