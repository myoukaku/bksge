/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ARRAY_CONFIG_HPP
#define BKSGE_FND_ARRAY_CONFIG_HPP

#include <bksge/fnd/config.hpp>
#include <array>

#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201811) && \
	defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907)
#  define BKSGE_USE_STD_ARRAY
#endif

#endif // BKSGE_FND_ARRAY_CONFIG_HPP
