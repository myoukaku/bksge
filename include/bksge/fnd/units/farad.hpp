/**
 *	@file	farad.hpp
 *
 *	@brief	farad の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_FARAD_HPP
#define BKSGE_FND_UNITS_FARAD_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/coulomb.hpp>
#include <bksge/fnd/units/volt.hpp>

namespace bksge
{

namespace units
{

// ファラド(静電容量の単位)
template <typename T> using farad  = decltype(coulomb<T>() / volt<T>());
template <typename T> using farads = farad<T>;
BKSGE_UNITS_SI_PREFIX(farad);
BKSGE_UNITS_SI_PREFIX(farads);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_FARAD_HPP
