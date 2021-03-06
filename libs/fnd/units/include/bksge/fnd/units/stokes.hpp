﻿/**
 *	@file	stokes.hpp
 *
 *	@brief	stokes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_STOKES_HPP
#define BKSGE_FND_UNITS_STOKES_HPP

#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// ストークス(動粘度の単位)
template <typename T> using stokes = decltype(centimetre<T>() * centimetre<T>() / second<T>());
// ※単数形・複数形ともstokes

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_STOKES_HPP
