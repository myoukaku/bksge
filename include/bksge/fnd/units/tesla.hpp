/**
 *	@file	tesla.hpp
 *
 *	@brief	tesla の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_TESLA_HPP
#define BKSGE_FND_UNITS_TESLA_HPP

#include <bksge/fnd/units/weber.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// テスラ(磁束密度の単位)
template <typename T> using tesla  = decltype(weber<T>() / metre<T>() / metre<T>());
template <typename T> using teslas = tesla<T>;
BKSGE_UNITS_SI_PREFIX(tesla);
BKSGE_UNITS_SI_PREFIX(teslas);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_TESLA_HPP
