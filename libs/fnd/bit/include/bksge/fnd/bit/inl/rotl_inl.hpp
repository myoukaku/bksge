/**
 *	@file	rotl_inl.hpp
 *
 *	@brief	rotl 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_ROTL_INL_HPP
#define BKSGE_FND_BIT_INL_ROTL_INL_HPP

#include <bksge/fnd/bit/rotl.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
rotl_impl(T x, unsigned int shift) BKSGE_NOEXCEPT
{
	return
		shift == 0 ?	// このチェックをしないとビット幅ぶんのシフトが発生して実装依存の動作になってしまう。
			x :
		static_cast<T>((x << shift) | (x >> (bitsof(x) - shift)));
}

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR T
rotl(T x, unsigned int shift) BKSGE_NOEXCEPT
{
	return detail::rotl_impl(x, shift & (bitsof(x) - 1));
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_ROTL_INL_HPP
