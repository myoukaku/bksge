/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPLEX_CONFIG_HPP
#define BKSGE_FND_COMPLEX_CONFIG_HPP

#include <bksge/fnd/config.hpp>
#include <complex>

#if defined(__cpp_lib_constexpr_complex) && (__cpp_lib_constexpr_complex >= 201711) && \
	defined(__cpp_lib_complex_udls) && (__cpp_lib_complex_udls >= 201309) && \
	defined(__STDC_IEC_559_COMPLEX__) && (__STDC_IEC_559_COMPLEX__ == 1)
#  define BKSGE_USE_STD_COMPLEX
#endif

// ISO IEC 60559 に準拠しているかどうか
#define BKSGE_IEC_559_COMPLEX

#endif // BKSGE_FND_COMPLEX_CONFIG_HPP
