/**
 *	@file	newton.hpp
 *
 *	@brief	newton の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_NEWTON_HPP
#define BKSGE_UNITS_NEWTON_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/gram.hpp>
#include <bksge/units/metre.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// ニュートン(kg・m/s^2)
template <typename T> using newton  = decltype(kilogram<T>() * metre<T>() / second<T>() / second<T>());
template <typename T> using newtons = newton<T>;
BKSGE_UNITS_SI_PREFIX(newton);
BKSGE_UNITS_SI_PREFIX(newtons);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_NEWTON_HPP
