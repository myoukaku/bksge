/**
 *	@file	acre.hpp
 *
 *	@brief	acre の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_ACRE_HPP
#define BKSGE_UNITS_ACRE_HPP

#include <bksge/units/yard.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// エーカー (4,840 平方ヤード = 4,046.8564224 平方メートル)
template <typename T> using acre  = decltype(yard<T>() * yard<T>() * std::ratio<4840>());
template <typename T> using acres = acre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_ACRE_HPP
