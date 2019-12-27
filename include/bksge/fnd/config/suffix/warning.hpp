/**
 *	@file	warning.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_WARNING_HPP
#define BKSGE_FND_CONFIG_SUFFIX_WARNING_HPP

//
//	BKSGE_WARNING_PUSH
//
#if !defined(BKSGE_WARNING_PUSH)
#	if defined(BKSGE_MSVC)
#	  define BKSGE_WARNING_PUSH()			BKSGE_PRAGMA(warning(push))
#	elif defined(BKSGE_CLANG)
#	  define BKSGE_WARNING_PUSH()			BKSGE_PRAGMA(clang diagnostic push)
#	elif defined(BKSGE_GCC)
#	  define BKSGE_WARNING_PUSH()			BKSGE_PRAGMA(GCC diagnostic push)
#	else
#	  define BKSGE_WARNING_PUSH()
#	endif
#endif

//
//	BKSGE_WARNING_POP
//
#if !defined(BKSGE_WARNING_POP)
#	if defined(BKSGE_MSVC)
#	  define BKSGE_WARNING_POP()			BKSGE_PRAGMA(warning(pop))
#	elif defined(BKSGE_CLANG)
#	  define BKSGE_WARNING_POP()			BKSGE_PRAGMA(clang diagnostic pop)
#	elif defined(BKSGE_GCC)
#	  define BKSGE_WARNING_POP()			BKSGE_PRAGMA(GCC diagnostic pop)
#	else
#	  define BKSGE_WARNING_POP()
#	endif
#endif

//
//	警告抑制マクロ
//
#if !defined(BKSGE_WARNING_DISABLE_MSVC)
#	if defined(BKSGE_MSVC)
#	  define BKSGE_WARNING_DISABLE_MSVC(x)	BKSGE_PRAGMA(warning(disable: x))
#	else
#	  define BKSGE_WARNING_DISABLE_MSVC(x)
#	endif
#endif

#if !defined(BKSGE_WARNING_DISABLE_CLANG)
#	if defined(BKSGE_CLANG)
#	  define BKSGE_WARNING_DISABLE_CLANG(x)	BKSGE_PRAGMA(clang diagnostic ignored x)
#	else
#	  define BKSGE_WARNING_DISABLE_CLANG(x)
#	endif
#endif

#if !defined(BKSGE_WARNING_DISABLE_GCC)
#	if defined(BKSGE_GCC)
#	  define BKSGE_WARNING_DISABLE_GCC(x)	BKSGE_PRAGMA(GCC diagnostic ignored x)
#	else
#	  define BKSGE_WARNING_DISABLE_GCC(x)
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_WARNING_HPP
