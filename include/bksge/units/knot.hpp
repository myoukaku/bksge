/**
 *	@file	knot.hpp
 *
 *	@brief	knot の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_KNOT_HPP
#define BKSGE_UNITS_KNOT_HPP

#include <bksge/units/metre.hpp>
#include <bksge/units/second.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// ノット
template <typename T> using knot  = decltype(metre<T>() / second<T>() * std::ratio<1852, 3600>());
template <typename T> using knots = knot<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_KNOT_HPP
