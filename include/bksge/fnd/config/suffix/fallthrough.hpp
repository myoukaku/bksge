/**
 *	@file	fallthrough.hpp
 *
 *	@brief	BKSGE_FALLTHROUGH の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_FALLTHROUGH_HPP
#define BKSGE_FND_CONFIG_SUFFIX_FALLTHROUGH_HPP

//
//	fallthrough workaround
//
#if !defined(BKSGE_FALLTHROUGH)
#	if defined(BKSGE_HAS_CXX17_FALLTHROUGH)
#		define BKSGE_FALLTHROUGH() [[fallthrough]]
#	elif BKSGE_HAS_ATTRIBUTE(fallthrough)
#		define BKSGE_FALLTHROUGH() __attribute__((__fallthrough__))
#	else
#		define BKSGE_FALLTHROUGH()
#		define BKSGE_NO_FALLTHROUGH
#	endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_FALLTHROUGH_HPP
