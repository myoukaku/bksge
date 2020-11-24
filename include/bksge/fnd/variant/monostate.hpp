/**
 *	@file	monostate.hpp
 *
 *	@brief	monostate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_MONOSTATE_HPP
#define BKSGE_FND_VARIANT_MONOSTATE_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::monostate;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		1つの状態だけを持つ型
 */
struct monostate {};

inline BKSGE_CONSTEXPR bool operator==(monostate, monostate) BKSGE_NOEXCEPT { return true; }

#if defined(__cpp_lib_three_way_comparison)

inline BKSGE_CONSTEXPR strong_ordering
operator<=>(monostate, monostate) BKSGE_NOEXCEPT { return strong_ordering::equal; }

#else

inline BKSGE_CONSTEXPR bool operator< (monostate, monostate) BKSGE_NOEXCEPT { return false; }
inline BKSGE_CONSTEXPR bool operator> (monostate, monostate) BKSGE_NOEXCEPT { return false; }
inline BKSGE_CONSTEXPR bool operator<=(monostate, monostate) BKSGE_NOEXCEPT { return true; }
inline BKSGE_CONSTEXPR bool operator>=(monostate, monostate) BKSGE_NOEXCEPT { return true; }
inline BKSGE_CONSTEXPR bool operator!=(monostate, monostate) BKSGE_NOEXCEPT { return false; }

#endif

}	// namespace bksge

#include <cstddef>
#include <functional>	// hash

namespace std
{

template <>
struct hash<bksge::monostate>
{
	std::size_t operator()(bksge::monostate const&) const BKSGE_NOEXCEPT
	{
		return 66740831; // return a fundamentally attractive random value.
	}
};

}	// namespace std

#endif

#endif // BKSGE_FND_VARIANT_MONOSTATE_HPP
