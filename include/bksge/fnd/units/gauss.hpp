/**
 *	@file	gauss.hpp
 *
 *	@brief	gauss の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_GAUSS_HPP
#define BKSGE_FND_UNITS_GAUSS_HPP

#include <bksge/fnd/units/maxwell.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// ガウス(磁束密度の単位)
template <typename T> using gauss   = decltype(maxwell<T>() / centimetre<T>() / centimetre<T>());
template <typename T> using gausses = gauss<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_GAUSS_HPP
