/**
 *	@file	alignas.hpp
 *
 *	@brief	BKSGE_ALIGNAS の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_ALIGNAS_HPP
#define BKSGE_CONFIG_SUFFIX_ALIGNAS_HPP

//
//	alignas workaround
//
#if !defined(BKSGE_ALIGNAS)
#  if defined(BKSGE_HAS_CXX11_ALIGNAS)
#    define BKSGE_ALIGNAS(x)      alignas(x)
#    define BKSGE_ALIGNAS_TYPE(x) alignas(x)
#  elif defined(_MSC_VER)
#    define BKSGE_ALIGNAS(x)      __declspec(align(x))
#    define BKSGE_ALIGNAS_TYPE(x) __declspec(align(__alignof(x)))
#  elif defined(__GNUC__)
#    define BKSGE_ALIGNAS(x)      __attribute__((__aligned__(x)))
#    define BKSGE_ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof__(x))))
#  else
#    define BKSGE_ALIGNAS(x)
#    define BKSGE_ALIGNAS_TYPE(x)
#    define BKSGE_NO_ALIGNAS
#  endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_ALIGNAS_HPP
