/**
 *	@file	coulomb.hpp
 *
 *	@brief	coulomb の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_COULOMB_HPP
#define BKSGE_UNITS_COULOMB_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/ampere.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// クーロン(電荷の単位)
template <typename T> using coulomb  = decltype(ampere<T>() * second<T>());
template <typename T> using coulombs = coulomb<T>;
BKSGE_UNITS_SI_PREFIX(coulomb);
BKSGE_UNITS_SI_PREFIX(coulombs);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_COULOMB_HPP
