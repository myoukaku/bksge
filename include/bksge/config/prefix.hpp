/**
 *	@file	prefix.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_PREFIX_HPP
#define BKSGE_CONFIG_PREFIX_HPP

//
// BKSGE_HAS_FEATURE
//
#if defined(__has_feature)
#	define BKSGE_HAS_FEATURE(x)		(__has_feature(x))
#else
#	define BKSGE_HAS_FEATURE(x)		(0)
#endif

//
// BKSGE_HAS_EXTENSION
//
#if defined(__has_extension)
#	define BKSGE_HAS_EXTENSION(x)	(__has_extension(x))
#else
#	define BKSGE_HAS_EXTENSION(x)	BKSGE_HAS_FEATURE(x)
#endif

//
// BKSGE_HAS_ATTRIBUTE
//
#if defined(__has_attribute)
#	define BKSGE_HAS_ATTRIBUTE(x)	(__has_attribute(x))
#else
#	define BKSGE_HAS_ATTRIBUTE(x)	(0)
#endif

//
// BKSGE_HAS_CPP_ATTRIBUTE
//
#if defined(__has_cpp_attribute)
#	define BKSGE_HAS_CPP_ATTRIBUTE(x)	(__has_cpp_attribute(x))
#else
#	define BKSGE_HAS_CPP_ATTRIBUTE(x)	(0)
#endif

//
// BKSGE_HAS_BUILTIN
//
#if defined(__has_builtin)
#	define BKSGE_HAS_BUILTIN(x)		(__has_builtin(x))
#else
#	define BKSGE_HAS_BUILTIN(x)		(0)
#endif

//
// BKSGE_HAS_WARNING
//
#if defined(__has_warning)
#	define BKSGE_HAS_WARNING(x)		(__has_warning(x))
#else
#	define BKSGE_HAS_WARNING(x)		(0)
#endif

//
// BKSGE_HAS_INCLUDE
//
#if defined(__has_include)
#	define BKSGE_HAS_INCLUDE(x)		(__has_include(x))
#else
#	define BKSGE_HAS_INCLUDE(x)		(0)
#endif

//
// BKSGE_HAS_KEYWORD
//
#if defined(__is_identifier)
#	define BKSGE_HAS_KEYWORD(x)		(!__is_identifier(x))
#else
#	define BKSGE_HAS_KEYWORD(x)		(0)
#endif

#endif // BKSGE_CONFIG_PREFIX_HPP
