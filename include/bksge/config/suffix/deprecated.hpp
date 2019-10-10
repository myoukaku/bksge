/**
 *	@file	deprecated.hpp
 *
 *	@brief	BKSGE_DEPRECATED の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_DEPRECATED_HPP
#define BKSGE_CONFIG_SUFFIX_DEPRECATED_HPP

//
//	[[deprecated]] workaround
//
#if !defined(BKSGE_DEPRECATED)
#	if defined(BKSGE_HAS_CXX14_DEPRECATED)
#		define BKSGE_DEPRECATED(message) [[deprecated(message)]]
#	elif defined(_MSC_VER)
#		define BKSGE_DEPRECATED(message) __declspec(deprecated(message))
#	elif defined(__GNUC__)
#		define BKSGE_DEPRECATED(message) __attribute__((deprecated(message)))
#	else
#		define BKSGE_DEPRECATED(message)
#		define BKSGE_NO_DEPRECATED
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_DEPRECATED_HPP
