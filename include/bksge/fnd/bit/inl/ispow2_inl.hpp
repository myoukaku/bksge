/**
 *	@file	ispow2_inl.hpp
 *
 *	@brief	ispow2 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_ISPOW2_INL_HPP
#define BKSGE_FND_BIT_INL_ISPOW2_INL_HPP

#include <bksge/fnd/bit/ispow2.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR bool
ispow2(T x) BKSGE_NOEXCEPT
{
	return x > 0 && ((x & (x - 1)) == 0);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_ISPOW2_INL_HPP
