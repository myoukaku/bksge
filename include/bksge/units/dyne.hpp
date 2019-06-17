/**
 *	@file	dyne.hpp
 *
 *	@brief	dyne の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DYNE_HPP
#define BKSGE_UNITS_DYNE_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/gram.hpp>
#include <bksge/units/metre.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// ダイン(g・cm/s^2)
template <typename T> using dyne  = decltype(gram<T>() * centimetre<T>() / second<T>() / second<T>());
template <typename T> using dynes = dyne<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_DYNE_HPP
