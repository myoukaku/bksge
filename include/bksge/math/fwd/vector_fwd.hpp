/**
 *	@file	vector_fwd.hpp
 *
 *	@brief	Vector の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_VECTOR_FWD_HPP
#define BKSGE_MATH_FWD_VECTOR_FWD_HPP

#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Vector;

}	// namespace math

using math::Vector;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_VECTOR_FWD_HPP
