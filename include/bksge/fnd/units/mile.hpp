/**
 *	@file	mile.hpp
 *
 *	@brief	mile の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MILE_HPP
#define BKSGE_FND_UNITS_MILE_HPP

#include <bksge/fnd/units/yard.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 国際マイル = 1760ヤード  (正確に1609.344m)
template <typename T> using mile  = decltype(yard<T>() * std::ratio<1760>());
template <typename T> using miles = mile<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MILE_HPP
