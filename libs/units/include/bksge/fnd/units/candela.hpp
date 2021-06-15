/**
 *	@file	candela.hpp
 *
 *	@brief	candela の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_CANDELA_HPP
#define BKSGE_FND_UNITS_CANDELA_HPP

#include <bksge/fnd/units/base_dimensions/luminous_intensity.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// カンデラ
template <typename T> using candela  = quantity<T, luminous_intensity_dimension>;
template <typename T> using candelas = candela<T>;
BKSGE_UNITS_SI_PREFIX(candela);
BKSGE_UNITS_SI_PREFIX(candelas);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_CANDELA_HPP
