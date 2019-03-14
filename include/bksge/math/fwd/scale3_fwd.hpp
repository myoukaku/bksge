﻿/**
 *	@file	scale3_fwd.hpp
 *
 *	@brief	Scale3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_SCALE3_FWD_HPP
#define BKSGE_MATH_FWD_SCALE3_FWD_HPP

#include <bksge/math/fwd/scale_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Scale3 = Scale<T, 3>;

}	// namespace math

using math::Scale3;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_SCALE3_FWD_HPP
