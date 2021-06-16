/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_CONFIG_HPP
#define BKSGE_FND_ANY_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<any>)
#  include <any>
#endif

#if defined(__cpp_lib_any) && (__cpp_lib_any >= 201606)
#  define BKSGE_USE_STD_ANY
#endif

#endif // BKSGE_FND_ANY_CONFIG_HPP
