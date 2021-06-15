/**
 *	@file	litre.hpp
 *
 *	@brief	litre の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_LITRE_HPP
#define BKSGE_FND_UNITS_LITRE_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// リットル
template <typename T> using litre  = decltype(decimetre<T>() * decimetre<T>() * decimetre<T>());
template <typename T> using litres = litre<T>;
template <typename T> using liter  = litre<T>;
template <typename T> using liters = litre<T>;
BKSGE_UNITS_SI_PREFIX(litre);
BKSGE_UNITS_SI_PREFIX(litres);
BKSGE_UNITS_SI_PREFIX(liter);
BKSGE_UNITS_SI_PREFIX(liters);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_LITRE_HPP
