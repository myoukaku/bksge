/**
 *	@file	alignof.hpp
 *
 *	@brief	BKSGE_ALIGNOF の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_ALIGNOF_HPP
#define BKSGE_CONFIG_SUFFIX_ALIGNOF_HPP

//
//	alignof workaround
//
#if !defined(BKSGE_ALIGNOF)
#	if !defined(BKSGE_NO_CXX11_ALIGNOF)
#		define BKSGE_ALIGNOF(type) alignof(type)
#	elif defined(_MSC_VER)
#		define BKSGE_ALIGNOF(type) __alignof(type)
#	elif defined(__GNUC__)
#		define BKSGE_ALIGNOF(type) __alignof__(type)
#	else
#		define BKSGE_ALIGNOF(type)
#		define BKSGE_NO_ALIGNOF
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_ALIGNOF_HPP
