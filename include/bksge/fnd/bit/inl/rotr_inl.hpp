/**
 *	@file	rotr_inl.hpp
 *
 *	@brief	rotr 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_ROTR_INL_HPP
#define BKSGE_FND_BIT_INL_ROTR_INL_HPP

#include <bksge/fnd/bit/rotr.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
rotr_impl(T x, unsigned int shift) BKSGE_NOEXCEPT
{
	return
		shift == 0 ?	// このチェックをしないとビット幅ぶんのシフトが発生して実装依存の動作になってしまう。
			x :
		static_cast<T>((x >> shift) | (x << (bitsof(x) - shift)));
}

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR T
rotr(T x, unsigned int shift) BKSGE_NOEXCEPT
{
	return detail::rotr_impl(x, shift & (bitsof(x) - 1));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_ROTR_INL_HPP
