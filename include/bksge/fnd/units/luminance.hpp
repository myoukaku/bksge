/**
 *	@file	luminance.hpp
 *
 *	@brief	luminance の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_LUMINANCE_HPP
#define BKSGE_FND_UNITS_LUMINANCE_HPP

#include <bksge/fnd/units/candela.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// カンデラ毎平方メートル(輝度の単位)
template <typename T> using candela_per_square_metre  = decltype(candela<T>() / metre<T>() / metre<T>());
template <typename T> using candelas_per_square_metre = candela_per_square_metre<T>;
template <typename T> using candela_per_square_meter  = candela_per_square_metre<T>;
template <typename T> using candelas_per_square_meter = candela_per_square_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_LUMINANCE_HPP
