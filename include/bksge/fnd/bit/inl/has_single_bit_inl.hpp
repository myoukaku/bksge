/**
 *	@file	has_single_bit_inl.hpp
 *
 *	@brief	has_single_bit 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_HAS_SINGLE_BIT_INL_HPP
#define BKSGE_FND_BIT_INL_HAS_SINGLE_BIT_INL_HPP

#include <bksge/fnd/bit/has_single_bit.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR bool
has_single_bit(T x) BKSGE_NOEXCEPT
{
	return x > 0 && ((x & (x - 1)) == 0);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_HAS_SINGLE_BIT_INL_HPP
