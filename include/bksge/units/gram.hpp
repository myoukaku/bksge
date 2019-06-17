/**
 *	@file	gram.hpp
 *
 *	@brief	gram の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_GRAM_HPP
#define BKSGE_UNITS_GRAM_HPP

#include <bksge/units/base_dimensions/mass.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// グラム
template <typename T> using gram  = quantity<T, mass_dimension>;
template <typename T> using grams = gram<T>;
BKSGE_UNITS_SI_PREFIX(gram);
BKSGE_UNITS_SI_PREFIX(grams);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_GRAM_HPP
