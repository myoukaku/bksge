/**
 *	@file	ounce.hpp
 *
 *	@brief	ounce の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_OUNCE_HPP
#define BKSGE_FND_UNITS_OUNCE_HPP

#include <bksge/fnd/units/pound.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 常用オンス = 1/16常用ポンド (正確に28.349523125グラム)
template <typename T> using ounce  = decltype(pound<T>() * std::ratio<1, 16>());
template <typename T> using ounces = ounce<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_OUNCE_HPP
