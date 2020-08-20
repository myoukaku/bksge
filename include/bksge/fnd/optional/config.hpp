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
#include <optional>
#endif

#if defined(__cpp_lib_optional) && (__cpp_lib_optional >= 201606)

// clang 8 より前のバージョンだとconstexpr対応が不十分なので、自前のoptionalを使う
#  if !(defined(BKSGE_CLANG_VERSION) && (BKSGE_CLANG_VERSION < 80000))

#    define	BKSGE_USE_STD_OPTIONAL

#  endif

#endif

#endif // BKSGE_FND_OPTIONAL_CONFIG_HPP
