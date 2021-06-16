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

#if defined(BKSGE_USE_STD_VARIANT)

namespace bksge
{

using std::monostate;

}	// namespace bksge

#else	// defined(BKSGE_USE_STD_VARIANT)

#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		1つの状態だけを持つ型
 */
struct monostate {};

inline BKSGE_CONSTEXPR bool operator==(monostate, monostate) BKSGE_NOEXCEPT { return true; }

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

inline BKSGE_CONSTEXPR bksge::strong_ordering
operator<=>(monostate, monostate) BKSGE_NOEXCEPT { return bksge::strong_ordering::equal; }

#else

inline BKSGE_CONSTEXPR bool operator< (monostate, monostate) BKSGE_NOEXCEPT { return false; }
inline BKSGE_CONSTEXPR bool operator> (monostate, monostate) BKSGE_NOEXCEPT { return false; }
inline BKSGE_CONSTEXPR bool operator<=(monostate, monostate) BKSGE_NOEXCEPT { return true; }
inline BKSGE_CONSTEXPR bool operator>=(monostate, monostate) BKSGE_NOEXCEPT { return true; }
inline BKSGE_CONSTEXPR bool operator!=(monostate, monostate) BKSGE_NOEXCEPT { return false; }

#endif

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_VARIANT)

#include <bksge/fnd/functional/config.hpp>

#if !defined(BKSGE_USE_STD_VARIANT) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <>
struct hash<bksge::monostate>
{
	bksge::size_t operator()(bksge::monostate const&) const BKSGE_NOEXCEPT
	{
		return 66740831; // return a fundamentally attractive random value.
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif	// !defined(BKSGE_USE_STD_VARIANT) || !defined(BKSGE_USE_STD_HASH)

#endif // BKSGE_FND_VARIANT_MONOSTATE_HPP
