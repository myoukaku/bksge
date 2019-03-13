/**
 *	@file	select_compiler_config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SELECT_COMPILER_CONFIG_HPP
#define BKSGE_CONFIG_SELECT_COMPILER_CONFIG_HPP

#if defined(__clang__) && !defined(__CUDACC__) && !defined(__ibmxl__)
// when using clang and cuda at same time, you want to appear as gcc
//  Clang C++ emulates GCC, so it has to appear early.
#   define BKSGE_COMPILER_CONFIG	"bksge/config/compiler/clang.hpp"

#elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#   define BKSGE_COMPILER_CONFIG	"bksge/config/compiler/gcc.hpp"

#elif defined(_MSC_VER)
//  Microsoft Visual C++
#   define BKSGE_COMPILER_CONFIG	"bksge/config/compiler/msvc.hpp"

#else
#	error "Unknown compiler"

#endif

#endif // BKSGE_CONFIG_SELECT_COMPILER_CONFIG_HPP
