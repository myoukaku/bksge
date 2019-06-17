/**
 *	@file	dynamic_viscosity.hpp
 *
 *	@brief	dynamic_viscosity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DYNAMIC_VISCOSITY_HPP
#define BKSGE_UNITS_DYNAMIC_VISCOSITY_HPP

#include <bksge/units/pascal.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// パスカル秒(粘度の単位)
template <typename T> using pascal_second  = decltype(pascals<T>() * second<T>());
template <typename T> using pascal_seconds = pascal_second<T>;

}	// namespace units

}	// namespace bksge

#include <bksge/units/poise.hpp>

#endif // BKSGE_UNITS_DYNAMIC_VISCOSITY_HPP
