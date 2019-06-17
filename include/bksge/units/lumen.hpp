/**
 *	@file	lumen.hpp
 *
 *	@brief	lumen の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_LUMEN_HPP
#define BKSGE_UNITS_LUMEN_HPP

#include <bksge/units/candela.hpp>
#include <bksge/units/steradian.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ルーメン(光束の単位)
template <typename T> using lumen  = decltype(candela<T>() * steradian<T>());
template <typename T> using lumens = lumen<T>;
BKSGE_UNITS_SI_PREFIX(lumen);
BKSGE_UNITS_SI_PREFIX(lumens);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_LUMEN_HPP
