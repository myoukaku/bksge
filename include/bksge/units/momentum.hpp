/**
 *	@file	momentum.hpp
 *
 *	@brief	momentum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MOMENTUM_HPP
#define BKSGE_UNITS_MOMENTUM_HPP

#include <bksge/units/newton.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// ニュートン秒(運動量の単位)
template <typename T> using newton_second  = decltype(newton<T>() * second<T>());
template <typename T> using newton_seconds = newton_second<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MOMENTUM_HPP
