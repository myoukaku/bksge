/**
 *	@file	torr.hpp
 *
 *	@brief	torr の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_TORR_HPP
#define BKSGE_FND_UNITS_TORR_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/pascal.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// トル = 101325 / 760 パスカル
template <typename T> using torr  = decltype(pascals<T>() * std::ratio<101325, 760>());
template <typename T> using torrs = torr<T>;
BKSGE_UNITS_SI_PREFIX(torr);
BKSGE_UNITS_SI_PREFIX(torrs);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_TORR_HPP
