/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BYTE_HPP
#define BKSGE_FND_UNITS_BYTE_HPP

#include <bksge/fnd/units/bit.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/detail/binary_prefix.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// バイト
template <typename T> using byte  = decltype(bit<T>() * bksge::ratio<8>());
template <typename T> using bytes = byte<T>;
BKSGE_UNITS_SI_PREFIX(byte);
BKSGE_UNITS_SI_PREFIX(bytes);
BKSGE_UNITS_BINARY_PREFIX(byte);
BKSGE_UNITS_BINARY_PREFIX(bytes);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_BYTE_HPP
