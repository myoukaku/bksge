/**
 *	@file	noreturn.hpp
 *
 *	@brief	BKSGE_NORETURN の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_NORETURN_HPP
#define BKSGE_CONFIG_SUFFIX_NORETURN_HPP

//
//	[[noreturn]] workaround
//
#if !defined(BKSGE_NORETURN)
#	if !defined(BKSGE_NO_CXX11_NORETURN)
#		define BKSGE_NORETURN [[noreturn]]
#	elif defined(_MSC_VER)
#		define BKSGE_NORETURN __declspec(noreturn)
#	elif defined(__GNUC__)
#		define BKSGE_NORETURN __attribute__ ((__noreturn__))
#	else
#		define BKSGE_NORETURN
#		define BKSGE_NO_NORETURN
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_NORETURN_HPP
