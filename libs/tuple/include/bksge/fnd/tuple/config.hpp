/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_CONFIG_HPP
#define BKSGE_FND_TUPLE_CONFIG_HPP

#include <bksge/fnd/config.hpp>
#include <tuple>

#if defined(__cpp_lib_constexpr_tuple) && (__cpp_lib_constexpr_tuple >= 201811) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907)
#  define BKSGE_USE_STD_TUPLE
#endif

#if defined(BKSGE_USE_STD_TUPLE)
#  define BKSGE_TUPLE_NAMESPACE std
#else
#  define BKSGE_TUPLE_NAMESPACE bksge
#endif

#endif // BKSGE_FND_TUPLE_CONFIG_HPP
