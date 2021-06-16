/**
 *	@file	mole.hpp
 *
 *	@brief	mole の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MOLE_HPP
#define BKSGE_FND_UNITS_MOLE_HPP

#include <bksge/fnd/units/base_dimensions/amount.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// モル
template <typename T> using mole  = quantity<T, amount_dimension>;
template <typename T> using moles = mole<T>;
BKSGE_UNITS_SI_PREFIX(mole);
BKSGE_UNITS_SI_PREFIX(moles);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MOLE_HPP
