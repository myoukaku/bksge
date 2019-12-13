/**
 *	@file	electrical_resistivity.hpp
 *
 *	@brief	electrical_resistivity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ELECTRICAL_RESISTIVITY_HPP
#define BKSGE_FND_UNITS_ELECTRICAL_RESISTIVITY_HPP

#include <bksge/fnd/units/ohm.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// オームメートル(電気抵抗率の単位)
template <typename T> using ohm_metre = decltype(ohm<T>() * metre<T>());
template <typename T> using ohm_meter = ohm_metre<T>;

// オームセンチメートル
template <typename T> using ohm_centimetre = decltype(ohm<T>() * centimetre<T>());
template <typename T> using ohm_centimeter = ohm_centimetre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ELECTRICAL_RESISTIVITY_HPP
