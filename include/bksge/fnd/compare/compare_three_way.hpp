/**
 *	@file	compare_three_way.hpp
 *
 *	@brief	compare_three_way の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_COMPARE_THREE_WAY_HPP
#define BKSGE_FND_COMPARE_COMPARE_THREE_WAY_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::compare_three_way;

}	// namespace bksge

#else	// defined(BKSGE_USE_STD_COMPARE)

#include <bksge/fnd/compare/detail/builtin_ptr_three_way.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable_with.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

struct compare_three_way
{
	template <typename T, typename U>
	requires bksge::three_way_comparable_with<T, U> || detail::builtin_ptr_three_way<T, U>
	constexpr auto operator()(T&& t, U&& u) const
		noexcept(noexcept(bksge::declval<T>() <=> bksge::declval<U>()))
	{
		if constexpr (detail::builtin_ptr_three_way<T, U>)
		{
			auto pt = static_cast<void const volatile*>(t);
			auto pu = static_cast<void const volatile*>(u);

			if (__builtin_is_constant_evaluated())
			{
				return pt <=> pu;
			}

			auto it = reinterpret_cast<std::uintptr_t>(pt);
			auto iu = reinterpret_cast<std::uintptr_t>(pu);
			return it <=> iu;
		}
		else
		{
			return static_cast<T&&>(t) <=> static_cast<U&&>(u);
		}
	}

	using is_transparent = void;
};

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_COMPARE)

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // BKSGE_FND_COMPARE_COMPARE_THREE_WAY_HPP
