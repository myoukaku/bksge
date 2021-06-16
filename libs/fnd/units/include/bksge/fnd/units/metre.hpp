/**
 *	@file	metre.hpp
 *
 *	@brief	metre の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_METRE_HPP
#define BKSGE_FND_UNITS_METRE_HPP

#include <bksge/fnd/units/base_dimensions/length.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// メートル
template <typename T> using metre  = quantity<T, length_dimension>;
template <typename T> using metres = metre<T>;
template <typename T> using meter  = metre<T>;
template <typename T> using meters = metre<T>;
BKSGE_UNITS_SI_PREFIX(metre);
BKSGE_UNITS_SI_PREFIX(metres);
BKSGE_UNITS_SI_PREFIX(meter);
BKSGE_UNITS_SI_PREFIX(meters);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_METRE_HPP
