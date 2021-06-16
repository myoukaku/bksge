/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_CONFIG_HPP
#define BKSGE_FND_STRING_VIEW_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<string_view>)
#  include <string_view>
#endif

#if (BKSGE_CXX_STANDARD >= 17) && \
	defined(__cpp_lib_starts_ends_with)      && (__cpp_lib_starts_ends_with      >= 201711) &&	\
	defined(__cpp_lib_string_view)           && (__cpp_lib_string_view           >= 201803) &&	\
	defined(__cpp_lib_constexpr_string_view) && (__cpp_lib_constexpr_string_view >= 201811) &&	\
	defined(__cpp_lib_three_way_comparison)  && (__cpp_lib_three_way_comparison  >= 201907) &&	\
	defined(__cpp_lib_char8_t)               && (__cpp_lib_char8_t               >= 201907) &&	\
	defined(__cpp_lib_string_contains)       && (__cpp_lib_string_contains       >= 202011)
#  define BKSGE_USE_STD_STRING_VIEW
#endif

#endif // BKSGE_FND_STRING_VIEW_CONFIG_HPP
