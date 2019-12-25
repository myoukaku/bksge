/**
 *	@file	log2p1_inl.hpp
 *
 *	@brief	log2p1 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_LOG2P1_INL_HPP
#define BKSGE_FND_BIT_INL_LOG2P1_INL_HPP

#include <bksge/fnd/bit/log2p1.hpp>
#include <bksge/fnd/bit/countl_zero.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR T
log2p1(T x) BKSGE_NOEXCEPT
{
	return static_cast<T>(bitsof(x) - countl_zero(x));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_LOG2P1_INL_HPP
