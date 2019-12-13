/**
 *	@file	dyne.hpp
 *
 *	@brief	dyne の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DYNE_HPP
#define BKSGE_FND_UNITS_DYNE_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/gram.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ダイン(g・cm/s^2)
template <typename T> using dyne  = decltype(gram<T>() * centimetre<T>() / second<T>() / second<T>());
template <typename T> using dynes = dyne<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DYNE_HPP
