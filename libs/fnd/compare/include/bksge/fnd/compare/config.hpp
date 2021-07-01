/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_CONFIG_HPP
#define BKSGE_FND_COMPARE_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if BKSGE_HAS_INCLUDE(<compare>) && (BKSGE_CXX_STANDARD >= 20)

#include <compare>

#define BKSGE_HAS_STD_COMPARE

#if defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)

#define BKSGE_USE_STD_COMPARE

#endif

#endif

// Visual Studio 2017 はinline変数に対応しているのに変数の多重定義でリンクエラーになる
#if defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)
#if !(defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920))
#define BKSGE_COMPARE_USE_INLINE_VARIABLES
#endif
#endif

#endif // BKSGE_FND_COMPARE_CONFIG_HPP
