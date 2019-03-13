/**
 *	@file	nodiscard.hpp
 *
 *	@brief	BKSGE_NODISCARD の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_NODISCARD_HPP
#define BKSGE_CONFIG_SUFFIX_NODISCARD_HPP

//
//	[[nodiscard]] workaround
//
#if !defined(BKSGE_NODISCARD)
#	if BKSGE_HAS_CPP_ATTRIBUTE(nodiscard)
#		define BKSGE_NODISCARD [[nodiscard]]
#	else
#		define BKSGE_NODISCARD
#		define BKSGE_NO_NODISCARD
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_NODISCARD_HPP
