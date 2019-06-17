﻿/**
 *	@file	tonne.hpp
 *
 *	@brief	tonne の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_TONNE_HPP
#define BKSGE_UNITS_TONNE_HPP

#include <bksge/units/gram.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// トン(メトリックトン) = 1000kg
template <typename T> using tonne  = decltype(kilogram<T>() * std::ratio<1000>());
template <typename T> using tonnes = tonne<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_TONNE_HPP
