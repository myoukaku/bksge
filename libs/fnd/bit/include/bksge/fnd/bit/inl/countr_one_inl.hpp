/**
 *	@file	countr_one_inl.hpp
 *
 *	@brief	countr_one 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_COUNTR_ONE_INL_HPP
#define BKSGE_FND_BIT_INL_COUNTR_ONE_INL_HPP

#include <bksge/fnd/bit/countr_one.hpp>
#include <bksge/fnd/bit/countr_zero.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename>
inline BKSGE_CONSTEXPR int
countr_one(T x) BKSGE_NOEXCEPT
{
	return countr_zero(static_cast<T>(~x));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_COUNTR_ONE_INL_HPP
