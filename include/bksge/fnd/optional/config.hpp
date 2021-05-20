/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_CONFIG_HPP
#define BKSGE_FND_OPTIONAL_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<optional>)
#if !(defined(BKSGE_MSVC_FULL_VER) && (192829910 <= BKSGE_MSVC_FULL_VER && BKSGE_MSVC_FULL_VER <= 192829915))
// Visual Studio 2019 version 16.9.(0-6) で <optional> をインクルードするとコンパイルエラーになる
#  include <optional>
#endif
#endif

#if (BKSGE_CXX_STANDARD >= 17) && \
	defined(__cpp_lib_optional) && (__cpp_lib_optional >= 201606) &&	\
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)

// clang 8 より前のバージョンだとconstexpr対応が不十分なので、自前のoptionalを使う
// gcc 8 より前のバージョンだとconstexpr対応が不十分なので、自前のoptionalを使う

#  if !(defined(BKSGE_CLANG_VERSION) && (BKSGE_CLANG_VERSION < 80000)) &&	\
      !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 80000))

#    define	BKSGE_USE_STD_OPTIONAL

#  endif

#endif

#endif // BKSGE_FND_OPTIONAL_CONFIG_HPP
