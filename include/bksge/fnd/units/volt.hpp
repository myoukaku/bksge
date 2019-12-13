/**
 *	@file	volt.hpp
 *
 *	@brief	volt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_VOLT_HPP
#define BKSGE_FND_UNITS_VOLT_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/watt.hpp>
#include <bksge/fnd/units/ampere.hpp>

namespace bksge
{

namespace units
{

// ボルト(電圧・電位差・起電力の単位)
template <typename T> using volt  = decltype(watt<T>() / ampere<T>());
template <typename T> using volts = volt<T>;
BKSGE_UNITS_SI_PREFIX(volt);
BKSGE_UNITS_SI_PREFIX(volts);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_VOLT_HPP
