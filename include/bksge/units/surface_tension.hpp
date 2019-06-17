/**
 *	@file	surface_tension.hpp
 *
 *	@brief	surface_tension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_SURFACE_TENSION_HPP
#define BKSGE_UNITS_SURFACE_TENSION_HPP

#include <bksge/units/newton.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// ニュートン毎メートル(表面張力の単位)
template <typename T> using newton_per_metre  = decltype(newton<T>() / metre<T>());
template <typename T> using newton_per_meter  = newton_per_metre<T>;
template <typename T> using newtons_per_metre = newton_per_metre<T>;
template <typename T> using newtons_per_meter = newton_per_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_SURFACE_TENSION_HPP
