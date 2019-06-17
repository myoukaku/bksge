/**
 *	@file	grain.hpp
 *
 *	@brief	grain の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_GRAIN_HPP
#define BKSGE_UNITS_GRAIN_HPP

#include <bksge/units/pound.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// グレーン = 1/7000常用ポンド(正確に0.06479891グラム)
template <typename T> using grain  = decltype(pound<T>() * std::ratio<1, 7000>());
template <typename T> using grains = grain<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_GRAIN_HPP
