/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BYTE_HPP
#define BKSGE_UNITS_BYTE_HPP

#include <bksge/units/bit.hpp>
#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/detail/binary_prefix.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// バイト
template <typename T> using byte  = decltype(bit<T>() * std::ratio<8>());
template <typename T> using bytes = byte<T>;
BKSGE_UNITS_SI_PREFIX(byte);
BKSGE_UNITS_SI_PREFIX(bytes);
BKSGE_UNITS_BINARY_PREFIX(byte);
BKSGE_UNITS_BINARY_PREFIX(bytes);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BYTE_HPP
