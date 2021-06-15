/**
 *	@file	bigint.hpp
 *
 *	@brief	bigint クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_BIGINT_HPP
#define BKSGE_FND_BIGINT_BIGINT_HPP

#include <bksge/fnd/bigint/basic_bigint.hpp>
#include <bksge/fnd/bigint/infinity_bits.hpp>

namespace bksge
{

// 無限ビット・符号付き
using bigint = bksge::basic_bigint<bksge::infinity_bits, true>;

// 固定ビット・符号付き
using int128_t  = bksge::basic_bigint< 128, true>;
using int256_t  = bksge::basic_bigint< 256, true>;
using int512_t  = bksge::basic_bigint< 512, true>;
using int1024_t = bksge::basic_bigint<1024, true>;
using int2048_t = bksge::basic_bigint<2048, true>;

// 固定ビット・符号なし
using uint128_t  = bksge::basic_bigint< 128, false>;
using uint256_t  = bksge::basic_bigint< 256, false>;
using uint512_t  = bksge::basic_bigint< 512, false>;
using uint1024_t = bksge::basic_bigint<1024, false>;
using uint2048_t = bksge::basic_bigint<2048, false>;

inline namespace literals {
inline namespace bigint_literals {

inline bksge::bigint operator "" _bigint(const char* str)
{
	return bksge::bigint(str);
}

#define BKSGE_BIGINT_LITERAL(T, L)					\
inline constexpr T operator "" L(const char* str)	\
{													\
	return T(str);									\
}

BKSGE_BIGINT_LITERAL(bksge::int128_t, _int128)
BKSGE_BIGINT_LITERAL(bksge::int256_t, _int256)
BKSGE_BIGINT_LITERAL(bksge::int512_t, _int512)
BKSGE_BIGINT_LITERAL(bksge::int1024_t, _int1024)
BKSGE_BIGINT_LITERAL(bksge::int2048_t, _int2048)
BKSGE_BIGINT_LITERAL(bksge::uint128_t, _uint128)
BKSGE_BIGINT_LITERAL(bksge::uint256_t, _uint256)
BKSGE_BIGINT_LITERAL(bksge::uint512_t, _uint512)
BKSGE_BIGINT_LITERAL(bksge::uint1024_t, _uint1024)
BKSGE_BIGINT_LITERAL(bksge::uint2048_t, _uint2048)

#undef BKSGE_BIGINT_LITERAL

}	// namespace bigint_literals
}	// namespace literals

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_BIGINT_HPP
