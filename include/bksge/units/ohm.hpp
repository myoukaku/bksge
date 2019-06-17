/**
 *	@file	ohm.hpp
 *
 *	@brief	ohm の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_OHM_HPP
#define BKSGE_UNITS_OHM_HPP

#include <bksge/units/volt.hpp>
#include <bksge/units/ampere.hpp>
#include <bksge/units/detail/si_prefix.hpp>

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

#endif // BKSGE_UNITS_OHM_HPP
