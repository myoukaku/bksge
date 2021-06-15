/**
 *	@file	grain.hpp
 *
 *	@brief	grain の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_GRAIN_HPP
#define BKSGE_FND_UNITS_GRAIN_HPP

#include <bksge/fnd/units/pound.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// グレーン = 1/7000常用ポンド(正確に0.06479891グラム)
template <typename T> using grain  = decltype(pound<T>() * bksge::ratio<1, 7000>());
template <typename T> using grains = grain<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_GRAIN_HPP
