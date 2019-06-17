/**
 *	@file	magnetic_permeability.hpp
 *
 *	@brief	magnetic_permeability の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MAGNETIC_PERMEABILITY_HPP
#define BKSGE_UNITS_MAGNETIC_PERMEABILITY_HPP

#include <bksge/units/henry.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// ヘンリー毎メートル(透磁率の単位)
template <typename T> using henry_per_metre   = decltype(henry<T>() / metre<T>());
template <typename T> using henry_per_meter   = henry_per_metre<T>;
template <typename T> using henries_per_metre = henry_per_metre<T>;
template <typename T> using henries_per_meter = henry_per_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MAGNETIC_PERMEABILITY_HPP
