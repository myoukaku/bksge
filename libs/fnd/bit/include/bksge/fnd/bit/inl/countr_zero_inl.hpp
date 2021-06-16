/**
 *	@file	countr_zero_inl.hpp
 *
 *	@brief	countr_zero 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_COUNTR_ZERO_INL_HPP
#define BKSGE_FND_BIT_INL_COUNTR_ZERO_INL_HPP

#include <bksge/fnd/bit/countr_zero.hpp>
#include <bksge/fnd/bit/popcount.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR int
countr_zero(T x) BKSGE_NOEXCEPT
{
	return popcount<T>(static_cast<T>((~x) & (x - 1)));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_COUNTR_ZERO_INL_HPP
