/**
 *	@file	final.hpp
 *
 *	@brief	BKSGE_FINAL の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_FINAL_HPP
#define BKSGE_FND_CONFIG_SUFFIX_FINAL_HPP

//
//	final workaround
//
#if !defined(BKSGE_FINAL)
#	if defined(BKSGE_HAS_CXX11_FINAL)
#		define BKSGE_FINAL final
#	else
#		define BKSGE_FINAL
#		define BKSGE_NO_FINAL
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_FINAL_HPP
