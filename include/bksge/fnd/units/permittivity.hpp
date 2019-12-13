/**
 *	@file	permittivity.hpp
 *
 *	@brief	permittivity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_PERMITTIVITY_HPP
#define BKSGE_FND_UNITS_PERMITTIVITY_HPP

#include <bksge/fnd/units/farad.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// ファラド毎メートル(誘電率の単位)
template <typename T> using farad_per_metre  = decltype(farad<T>() / metre<T>());
template <typename T> using farad_per_meter  = farad_per_metre<T>;
template <typename T> using farads_per_metre = farad_per_metre<T>;
template <typename T> using farads_per_meter = farad_per_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_PERMITTIVITY_HPP
