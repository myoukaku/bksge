/**
 *	@file	unreachable.hpp
 *
 *	@brief	BKSGE_UNREACHABLE の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_UNREACHABLE_HPP
#define BKSGE_CONFIG_SUFFIX_UNREACHABLE_HPP

//
//	unreachable workaround
//
#if !defined(BKSGE_UNREACHABLE)
#  ifdef __GNUC__
#    define BKSGE_UNREACHABLE() __builtin_unreachable()
#  else
#    define BKSGE_UNREACHABLE()
#  endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_UNREACHABLE_HPP
