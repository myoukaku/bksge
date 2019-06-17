/**
 *	@file	inch.hpp
 *
 *	@brief	inch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_INCH_HPP
#define BKSGE_UNITS_INCH_HPP

#include <bksge/units/metre.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 国際インチ  (正確に25.4mm)
template <typename T> using inch   = decltype(metre<T>() * std::ratio<254, 10000>());
template <typename T> using inches = inch<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_INCH_HPP
