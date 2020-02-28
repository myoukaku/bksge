/**
 *	@file	matrix_fwd.hpp
 *
 *	@brief	Matrix の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_MATRIX_FWD_HPP
#define BKSGE_CORE_MATH_FWD_MATRIX_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N, bksge::size_t M>
class Matrix;

}	// namespace math

using math::Matrix;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_MATRIX_FWD_HPP
