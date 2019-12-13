/**
 *	@file	knot.hpp
 *
 *	@brief	knot の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_KNOT_HPP
#define BKSGE_FND_UNITS_KNOT_HPP

#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/second.hpp>
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

#endif // BKSGE_FND_UNITS_KNOT_HPP
