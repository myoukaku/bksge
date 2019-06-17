/**
 *	@file	erg.hpp
 *
 *	@brief	erg の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_ERG_HPP
#define BKSGE_UNITS_ERG_HPP

#include <bksge/units/dyne.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// エルグ(dyn・cm)
template <typename T> using erg  = decltype(dyne<T>() * centimetre<T>());
template <typename T> using ergs = erg<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_ERG_HPP
