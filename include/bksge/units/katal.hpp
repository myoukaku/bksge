/**
 *	@file	katal.hpp
 *
 *	@brief	katal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_KATAL_HPP
#define BKSGE_UNITS_KATAL_HPP

#include <bksge/units/mole.hpp>
#include <bksge/units/second.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// カタール(酵素活性（触媒活性）の単位)
template <typename T> using katal  = decltype(mole<T>() / second<T>());
template <typename T> using katals = katal<T>;
BKSGE_UNITS_SI_PREFIX(katal);
BKSGE_UNITS_SI_PREFIX(katals);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_KATAL_HPP
