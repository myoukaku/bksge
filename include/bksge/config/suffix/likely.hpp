/**
 *	@file	likely.hpp
 *
 *	@brief	BKSGE_LIKELY の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_LIKELY_HPP
#define BKSGE_CONFIG_SUFFIX_LIKELY_HPP

//
//	分岐予測ヒント
//
#if !defined(BKSGE_LIKELY)
#  if BKSGE_HAS_BUILTIN(__builtin_expect)
#    define BKSGE_LIKELY(x) __builtin_expect(x, 1)
#  else
#    define BKSGE_LIKELY(x) x
#  endif
#endif

#if !defined(BKSGE_UNLIKELY)
#  if BKSGE_HAS_BUILTIN(__builtin_expect)
#    define BKSGE_UNLIKELY(x) __builtin_expect(x, 0)
#  else
#    define BKSGE_UNLIKELY(x) x
#  endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_LIKELY_HPP
