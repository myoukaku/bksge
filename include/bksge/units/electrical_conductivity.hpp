/**
 *	@file	electrical_conductivity.hpp
 *
 *	@brief	electrical_conductivity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_ELECTRICAL_CONDUCTIVITY_HPP
#define BKSGE_UNITS_ELECTRICAL_CONDUCTIVITY_HPP

#include <bksge/units/siemens.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// ジーメンス毎メートル(電気伝導率の単位)
template <typename T> using siemens_per_metre = decltype(siemens<T>() / metre<T>());
template <typename T> using siemens_per_meter = siemens_per_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_ELECTRICAL_CONDUCTIVITY_HPP
