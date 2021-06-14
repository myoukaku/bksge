/**
 *	@file	override.hpp
 *
 *	@brief	BKSGE_OVERRIDE の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_OVERRIDE_HPP
#define BKSGE_FND_CONFIG_SUFFIX_OVERRIDE_HPP

//
//	override workaround
//
#if !defined(BKSGE_OVERRIDE)
#	if defined(BKSGE_HAS_CXX11_OVERRIDE)
#		define BKSGE_OVERRIDE override
#	else
#		define BKSGE_OVERRIDE
#		define BKSGE_NO_OVERRIDE
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_OVERRIDE_HPP
