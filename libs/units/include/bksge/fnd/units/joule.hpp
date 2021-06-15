/**
 *	@file	joule.hpp
 *
 *	@brief	joule の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_JOULE_HPP
#define BKSGE_FND_UNITS_JOULE_HPP

#include <bksge/fnd/units/newton.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ジュール(kg・m^2 / s^2 = N・m)
template <typename T> using joule  = decltype(newton<T>() * metre<T>());
template <typename T> using joules = joule<T>;
BKSGE_UNITS_SI_PREFIX(joule);
BKSGE_UNITS_SI_PREFIX(joules);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_JOULE_HPP
