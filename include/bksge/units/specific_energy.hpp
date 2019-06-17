/**
 *	@file	specific_energy.hpp
 *
 *	@brief	specific_energy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_SPECIFIC_ENERGY_HPP
#define BKSGE_UNITS_SPECIFIC_ENERGY_HPP

#include <bksge/units/joule.hpp>
#include <bksge/units/gram.hpp>

namespace bksge
{

namespace units
{

// ジュール毎キログラム(比エネルギーの単位)
template <typename T> using joule_per_kilogram  = decltype(joule<T>() / kilogram<T>());
template <typename T> using joules_per_kilogram = joule_per_kilogram<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_SPECIFIC_ENERGY_HPP
