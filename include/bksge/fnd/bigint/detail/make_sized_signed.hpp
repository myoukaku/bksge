/**
 *	@file	make_sized_signed.hpp
 *
 *	@brief	make_sized_signed クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP
#define BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace detail
{

template <bksge::size_t N>
struct make_sized_signed{};

template <bksge::size_t N>
using make_sized_signed_t = typename make_sized_signed<N>::type;

template <> struct make_sized_signed<1> {using type = bksge::int8_t; };
template <> struct make_sized_signed<2> {using type = bksge::int16_t; };
template <> struct make_sized_signed<4> {using type = bksge::int32_t; };
template <> struct make_sized_signed<8> {using type = bksge::int64_t; };

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MAKE_SIZED_SIGNED_HPP
