/**
 *	@file	make_sized_signed.hpp
 *
 *	@brief	make_sized_signed クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP
#define BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP

#include <cstddef>
#include <cstdint>

namespace bksge
{

namespace detail
{

template <std::size_t N>
struct make_sized_signed{};

template <std::size_t N>
using make_sized_signed_t = typename make_sized_signed<N>::type;

template <> struct make_sized_signed<1> {using type = std::int8_t; };
template <> struct make_sized_signed<2> {using type = std::int16_t; };
template <> struct make_sized_signed<4> {using type = std::int32_t; };
template <> struct make_sized_signed<8> {using type = std::int64_t; };

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP
