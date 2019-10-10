/**
 *	@file	carries_dependency.hpp
 *
 *	@brief	BKSGE_CARRIES_DEPENDENCY の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP
#define BKSGE_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP

//
//	[[carries_dependency]] workaround
//
#if !defined(BKSGE_CARRIES_DEPENDENCY)
#	if defined(BKSGE_HAS_CXX11_CARRIES_DEPENDENCY)
#		define BKSGE_CARRIES_DEPENDENCY [[carries_dependency]]
#	else
#		define BKSGE_CARRIES_DEPENDENCY
#		define BKSGE_NO_CARRIES_DEPENDENCY
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_CARRIES_DEPENDENCY_HPP
