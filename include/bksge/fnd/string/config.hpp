/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_CONFIG_HPP
#define BKSGE_FND_STRING_CONFIG_HPP

#include <bksge/fnd/config.hpp>
#include <bksge/fnd/string_view/config.hpp>
#include <string>

#if defined(BKSGE_USE_STD_STRING_VIEW) && \
	defined(__cpp_lib_string_udls)           && (__cpp_lib_string_udls           >= 201304) &&	\
	defined(__cpp_lib_starts_ends_with)      && (__cpp_lib_starts_ends_with      >= 201711) &&	\
	defined(__cpp_lib_constexpr_string)      && (__cpp_lib_constexpr_string      >= 201907) &&	\
	defined(__cpp_lib_three_way_comparison)  && (__cpp_lib_three_way_comparison  >= 201907) &&	\
	defined(__cpp_lib_char8_t)               && (__cpp_lib_char8_t               >= 201907) &&	\
	defined(__cpp_lib_erase_if)              && (__cpp_lib_erase_if              >= 202002) &&	\
	defined(__cpp_lib_string_contains)       && (__cpp_lib_string_contains       >= 202011)
#  define BKSGE_USE_STD_STRING
#endif

#endif // BKSGE_FND_STRING_CONFIG_HPP
