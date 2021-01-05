/**
 *	@file	inch.hpp
 *
 *	@brief	inch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_INCH_HPP
#define BKSGE_FND_UNITS_INCH_HPP

#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 国際インチ  (正確に25.4mm)
template <typename T> using inch   = decltype(metre<T>() * bksge::ratio<254, 10000>());
template <typename T> using inches = inch<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_INCH_HPP
