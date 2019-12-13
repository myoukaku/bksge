/**
 *	@file	pragma.hpp
 *
 *	@brief	BKSGE_PRAGMA の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_PRAGMA_HPP
#define BKSGE_FND_CONFIG_SUFFIX_PRAGMA_HPP

//
//	Pragma演算子
//
#if !defined(BKSGE_PRAGMA)
#	if defined(BKSGE_HAS_CXX11_PRAGMA_OPERATOR)
#	  define BKSGE_PRAGMA(x)		_Pragma(#x)
#	else
#	  define BKSGE_PRAGMA(x)		__pragma(x)
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_PRAGMA_HPP
