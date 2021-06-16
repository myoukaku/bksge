/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_CONFIG_HPP
#define BKSGE_FND_VARIANT_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<variant>)
#  include <variant>
#endif

#if defined(__cpp_lib_variant) && (__cpp_lib_variant >= 201606)
#  define BKSGE_USE_STD_VARIANT
#endif

#endif // BKSGE_FND_VARIANT_CONFIG_HPP
