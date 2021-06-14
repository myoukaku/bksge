/**
 *	@file	decompose_float.hpp
 *
 *	@brief	decompose_float 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DECOMPOSE_FLOAT_HPP
#define BKSGE_FND_CMATH_DECOMPOSE_FLOAT_HPP

#include <bksge/fnd/cmath/detail/decompose_float_impl.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	浮動小数点数を仮数、指数、符号に分解する
 *
 *	似たような関数のfrexpと違い、この関数は仮数を整数値で取得する。
 *	得られた符号をs、仮数をf、指数をeとしたとき、
 *	-1^s * f * 2^e
 *	で元の浮動小数点数と同じになる。
 */
template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CONSTEXPR decompose_float_result_t<Float>
decompose_float(Float x) BKSGE_NOEXCEPT
{
	return detail::decompose_float_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DECOMPOSE_FLOAT_HPP
