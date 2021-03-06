﻿/**
 *	@file	bit_width_inl.hpp
 *
 *	@brief	bit_width 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_BIT_WIDTH_INL_HPP
#define BKSGE_FND_BIT_INL_BIT_WIDTH_INL_HPP

#include <bksge/fnd/bit/bit_width.hpp>
#include <bksge/fnd/bit/countl_zero.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR T
bit_width(T x) BKSGE_NOEXCEPT
{
	return static_cast<T>(bitsof(x) - countl_zero(x));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_BIT_WIDTH_INL_HPP
