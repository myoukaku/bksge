/**
 *	@file	bit.hpp
 *
 *	@brief	bit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BIT_HPP
#define BKSGE_UNITS_BIT_HPP

#include <bksge/units/base_dimensions/information.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/detail/binary_prefix.hpp>

namespace bksge
{

namespace units
{

// ビット
template <typename T> using bit  = quantity<T, information_dimension>;
template <typename T> using bits = bit<T>;
BKSGE_UNITS_SI_PREFIX(bit);
BKSGE_UNITS_SI_PREFIX(bits);
BKSGE_UNITS_BINARY_PREFIX(bit);
BKSGE_UNITS_BINARY_PREFIX(bits);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BIT_HPP
