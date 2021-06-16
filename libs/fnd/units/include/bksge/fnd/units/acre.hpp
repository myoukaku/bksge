/**
 *	@file	acre.hpp
 *
 *	@brief	acre の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ACRE_HPP
#define BKSGE_FND_UNITS_ACRE_HPP

#include <bksge/fnd/units/yard.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// エーカー (4,840 平方ヤード = 4,046.8564224 平方メートル)
template <typename T> using acre  = decltype(yard<T>() * yard<T>() * bksge::ratio<4840>());
template <typename T> using acres = acre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ACRE_HPP
