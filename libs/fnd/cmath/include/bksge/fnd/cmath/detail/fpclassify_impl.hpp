/**
 *	@file	fpclassify_impl.hpp
 *
 *	@brief	fpclassify 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FPCLASSIFY_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FPCLASSIFY_IMPL_HPP

#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR int
fpclassify_impl(FloatType x) BKSGE_NOEXCEPT
{
	return std::fpclassify(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FPCLASSIFY_IMPL_HPP
