/**
 *	@file	weber.hpp
 *
 *	@brief	weber の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_WEBER_HPP
#define BKSGE_UNITS_WEBER_HPP

#include <bksge/units/volt.hpp>
#include <bksge/units/second.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ウェーバ(磁束の単位)
template <typename T> using weber  = decltype(volt<T>() * second<T>());
template <typename T> using webers = weber<T>;
BKSGE_UNITS_SI_PREFIX(weber);
BKSGE_UNITS_SI_PREFIX(webers);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_WEBER_HPP
