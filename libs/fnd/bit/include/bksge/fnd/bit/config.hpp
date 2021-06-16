/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_CONFIG_HPP
#define BKSGE_FND_BIT_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>)
#include <bit>

#  if defined(__cpp_lib_endian) && (__cpp_lib_endian >= 201907)
#    define BKSGE_HAS_CXX_LIB_ENDIAN
#  endif
#  if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806)
#    define BKSGE_HAS_CXX_LIB_BIT_CAST
#  endif
#  if defined(__cpp_lib_bitops) && (__cpp_lib_bitops >= 201907)
#    define BKSGE_HAS_CXX_LIB_BITOPS
#  endif
#  if defined(__cpp_lib_int_pow2) && (__cpp_lib_int_pow2 >= 202002)
#    define BKSGE_HAS_CXX_LIB_INT_POW2
#  endif

#endif

#endif // BKSGE_FND_BIT_CONFIG_HPP
