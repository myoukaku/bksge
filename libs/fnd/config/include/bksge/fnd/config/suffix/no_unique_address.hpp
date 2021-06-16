/**
 *	@file	no_unique_address.hpp
 *
 *	@brief	BKSGE_NO_UNIQUE_ADDRESS の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP
#define BKSGE_FND_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP

//
//	[[no_unique_address]] workaround
//
#if !defined(BKSGE_NO_UNIQUE_ADDRESS)
#	if defined(BKSGE_HAS_CXX20_NO_UNIQUE_ADDRESS)
#		define BKSGE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#	else
#		define BKSGE_NO_UNIQUE_ADDRESS
#		define BKSGE_NO_NO_UNIQUE_ADDRESS
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_NO_UNIQUE_ADDRESS_HPP
