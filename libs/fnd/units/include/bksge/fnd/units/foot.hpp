/**
 *	@file	foot.hpp
 *
 *	@brief	foot の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_FOOT_HPP
#define BKSGE_FND_UNITS_FOOT_HPP

#include <bksge/fnd/units/inch.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 国際フィート = 12インチ(正確に0.3048m)
template <typename T> using foot = decltype(inch<T>() * bksge::ratio<12>());
template <typename T> using feet = foot<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_FOOT_HPP
