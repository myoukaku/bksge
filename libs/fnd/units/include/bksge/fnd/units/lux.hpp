/**
 *	@file	lux.hpp
 *
 *	@brief	lux の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_LUX_HPP
#define BKSGE_FND_UNITS_LUX_HPP

#include <bksge/fnd/units/lumen.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ルクス(照度の単位)
template <typename T> using lux  = decltype(lumen<T>() / metre<T>() / metre<T>());
BKSGE_UNITS_SI_PREFIX(lux);
// ※単数形・複数形ともlux

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_LUX_HPP
