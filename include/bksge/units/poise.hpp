/**
 *	@file	poise.hpp
 *
 *	@brief	poise の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_POISE_HPP
#define BKSGE_UNITS_POISE_HPP

#include <bksge/units/dyne.hpp>
#include <bksge/units/second.hpp>
#include <bksge/units/metre.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ポアズ(粘度の単位)
template <typename T> using poise  = decltype(dyne<T>() * second<T>() / (centimetre<T>() * centimetre<T>()));
template <typename T> using poises = poise<T>;
BKSGE_UNITS_SI_PREFIX(poise);
BKSGE_UNITS_SI_PREFIX(poises);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_POISE_HPP
