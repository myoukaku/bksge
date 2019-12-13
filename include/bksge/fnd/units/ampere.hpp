/**
 *	@file	ampere.hpp
 *
 *	@brief	ampere の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_AMPERE_HPP
#define BKSGE_FND_UNITS_AMPERE_HPP

#include <bksge/fnd/units/base_dimensions/current.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// アンペア
template <typename T> using ampere  = quantity<T, current_dimension>;
template <typename T> using amperes = ampere<T>;
BKSGE_UNITS_SI_PREFIX(ampere);
BKSGE_UNITS_SI_PREFIX(amperes);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_AMPERE_HPP
