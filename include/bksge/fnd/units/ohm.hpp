/**
 *	@file	ohm.hpp
 *
 *	@brief	ohm の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_OHM_HPP
#define BKSGE_FND_UNITS_OHM_HPP

#include <bksge/fnd/units/volt.hpp>
#include <bksge/fnd/units/ampere.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// オーム(電気抵抗の単位)
template <typename T> using ohm  = decltype(volt<T>() / ampere<T>());
template <typename T> using ohms = ohm<T>;
BKSGE_UNITS_SI_PREFIX(ohm);
BKSGE_UNITS_SI_PREFIX(ohms);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_OHM_HPP
