/**
 *	@file	yard.hpp
 *
 *	@brief	yard の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_YARD_HPP
#define BKSGE_FND_UNITS_YARD_HPP

#include <bksge/fnd/units/foot.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 国際ヤード = 3フィート (正確に0.9144m)
template <typename T> using yard  = decltype(foot<T>() * bksge::ratio<3>());
template <typename T> using yards = yard<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_YARD_HPP
