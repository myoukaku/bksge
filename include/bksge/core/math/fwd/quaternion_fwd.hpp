/**
 *	@file	quaternion_fwd.hpp
 *
 *	@brief	Quaternion の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_QUATERNION_FWD_HPP
#define BKSGE_CORE_MATH_FWD_QUATERNION_FWD_HPP

namespace bksge
{

namespace math
{

template <typename T>
class Quaternion;

using Quaternionf = Quaternion<float>;

}	// namespace math

using math::Quaternion;
using math::Quaternionf;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_QUATERNION_FWD_HPP
