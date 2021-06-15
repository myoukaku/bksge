/**
 *	@file	gal.hpp
 *
 *	@brief	gal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_GAL_HPP
#define BKSGE_FND_UNITS_GAL_HPP

#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ガル
template <typename T> using gal  = decltype(centimetre<T>() / second<T>() / second<T>());
template <typename T> using gals = gal<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_GAL_HPP
