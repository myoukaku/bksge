/**
 *	@file	dynamic_viscosity.hpp
 *
 *	@brief	dynamic_viscosity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DYNAMIC_VISCOSITY_HPP
#define BKSGE_FND_UNITS_DYNAMIC_VISCOSITY_HPP

#include <bksge/fnd/units/pascal.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// パスカル秒(粘度の単位)
template <typename T> using pascal_second  = decltype(pascals<T>() * second<T>());
template <typename T> using pascal_seconds = pascal_second<T>;

}	// namespace units

}	// namespace bksge

#include <bksge/fnd/units/poise.hpp>

#endif // BKSGE_FND_UNITS_DYNAMIC_VISCOSITY_HPP
