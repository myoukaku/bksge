/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_CONFIG_HPP
#define BKSGE_FND_FUNCTIONAL_CONFIG_HPP

#include <bksge/fnd/config.hpp>
#include <functional>

#if BKSGE_CXX_STANDARD >= 17
#  if defined(__cpp_lib_transparent_operators) && (__cpp_lib_transparent_operators >= 201210)
#    define BKSGE_USE_STD_FUNCTIONAL_OPERATORS
#  endif
#endif

//#define BKSGE_USE_STD_HASH

#if defined(BKSGE_USE_STD_HASH)
#  define BKSGE_HASH_NAMESPACE std
#else
#  define BKSGE_HASH_NAMESPACE bksge
#endif

#endif // BKSGE_FND_FUNCTIONAL_CONFIG_HPP
