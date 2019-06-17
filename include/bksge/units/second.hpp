/**
 *	@file	second.hpp
 *
 *	@brief	second の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_SECOND_HPP
#define BKSGE_UNITS_SECOND_HPP

#include <bksge/units/base_dimensions/time.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// 秒
template <typename T> using second  = quantity<T, time_dimension>;
template <typename T> using seconds = second<T>;
BKSGE_UNITS_SI_PREFIX(second);
BKSGE_UNITS_SI_PREFIX(seconds);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_SECOND_HPP
