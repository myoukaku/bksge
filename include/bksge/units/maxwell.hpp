/**
 *	@file	maxwell.hpp
 *
 *	@brief	maxwell の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MAXWELL_HPP
#define BKSGE_UNITS_MAXWELL_HPP

#include <bksge/units/volt.hpp>
#include <bksge/units/second.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// マクスウェル(磁束の単位)
template <typename T> using maxwell  = decltype(volt<T>() * second<T>() * std::ratio<1, 100000000>());
template <typename T> using maxwells = maxwell<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MAXWELL_HPP
