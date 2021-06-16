/**
 *	@file	vector_fwd.hpp
 *
 *	@brief	Vector の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_VECTOR_FWD_HPP
#define BKSGE_CORE_MATH_FWD_VECTOR_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
class Vector;

}	// namespace math

using math::Vector;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_VECTOR_FWD_HPP
