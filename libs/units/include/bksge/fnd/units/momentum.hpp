/**
 *	@file	momentum.hpp
 *
 *	@brief	momentum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MOMENTUM_HPP
#define BKSGE_FND_UNITS_MOMENTUM_HPP

#include <bksge/fnd/units/newton.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ニュートン秒(運動量の単位)
template <typename T> using newton_second  = decltype(newton<T>() * second<T>());
template <typename T> using newton_seconds = newton_second<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MOMENTUM_HPP
