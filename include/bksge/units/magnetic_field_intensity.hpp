/**
 *	@file	magnetic_field_intensity.hpp
 *
 *	@brief	magnetic_field_intensity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MAGNETIC_FIELD_INTENSITY_HPP
#define BKSGE_UNITS_MAGNETIC_FIELD_INTENSITY_HPP

#include <bksge/units/ampere.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// アンペア毎メートル(磁場（磁界）の強さの単位)
template <typename T> using ampere_per_metre  = decltype(ampere<T>() / metre<T>());
template <typename T> using ampere_per_meter  = ampere_per_metre<T>;
template <typename T> using amperes_per_metre = ampere_per_metre<T>;
template <typename T> using amperes_per_meter = ampere_per_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MAGNETIC_FIELD_INTENSITY_HPP
