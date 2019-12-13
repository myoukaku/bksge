/**
 *	@file	sievert.hpp
 *
 *	@brief	sievert の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_SIEVERT_HPP
#define BKSGE_FND_UNITS_SIEVERT_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/gram.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// シーベルト(線量当量・等価線量の単位)
template <typename T> using sievert  = decltype(joule<T>() / kilogram<T>());
template <typename T> using sieverts = sievert<T>;
BKSGE_UNITS_SI_PREFIX(sievert);
BKSGE_UNITS_SI_PREFIX(sieverts);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_SIEVERT_HPP
