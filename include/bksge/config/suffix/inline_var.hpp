/**
 *	@file	inline_var.hpp
 *
 *	@brief	BKSGE_INLINE_VAR の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_INLINE_VAR_HPP
#define BKSGE_CONFIG_SUFFIX_INLINE_VAR_HPP

//
//	inline variables workaround
//
#if !defined(BKSGE_INLINE_VAR)
#	if !defined(BKSGE_NO_CXX17_INLINE_VARIABLES)
#		define BKSGE_INLINE_VAR inline
#	else
#		define BKSGE_INLINE_VAR
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_INLINE_VAR_HPP
