/**
 *	@file	make_sized_unsigned.hpp
 *
 *	@brief	make_sized_unsigned クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_UNSIGNED_HPP
#define BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_UNSIGNED_HPP

#include <cstddef>
#include <cstdint>

namespace bksge
{

namespace detail
{

template <std::size_t N>
struct make_sized_unsigned{};

template <std::size_t N>
using make_sized_unsigned_t = typename make_sized_unsigned<N>::type;

template <> struct make_sized_unsigned<1> {using type = std::uint8_t; };
template <> struct make_sized_unsigned<2> {using type = std::uint16_t; };
template <> struct make_sized_unsigned<4> {using type = std::uint32_t; };
template <> struct make_sized_unsigned<8> {using type = std::uint64_t; };

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_UNSIGNED_HPP
