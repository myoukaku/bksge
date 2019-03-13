/**
 *	@file	constexpr.hpp
 *
 *	@brief	BKSGE_CONSTEXPR の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_CONSTEXPR_HPP
#define BKSGE_CONFIG_SUFFIX_CONSTEXPR_HPP

//
// constexpr workarounds
//
#if !defined(BKSGE_CONSTEXPR)
#  if defined(BKSGE_NO_CXX11_CONSTEXPR)
#    define BKSGE_CONSTEXPR
#  else
#    define BKSGE_CONSTEXPR constexpr
#  endif
#endif

#if !defined(BKSGE_CONSTEXPR_OR_CONST)
# if defined(BKSGE_NO_CXX11_CONSTEXPR)
#   define BKSGE_CONSTEXPR_OR_CONST const
# else
#   define BKSGE_CONSTEXPR_OR_CONST constexpr
# endif
#endif

#if !defined(BKSGE_CXX14_CONSTEXPR)
#  if defined(BKSGE_NO_CXX14_CONSTEXPR)
#    define BKSGE_CXX14_CONSTEXPR
#  else
#    define BKSGE_CXX14_CONSTEXPR constexpr
#  endif
#endif

#if !defined(BKSGE_CXX14_CONSTEXPR_OR_CONST)
#  if defined(BKSGE_NO_CXX14_CONSTEXPR)
#    define BKSGE_CXX14_CONSTEXPR_OR_CONST const
#  else
#    define BKSGE_CXX14_CONSTEXPR_OR_CONST constexpr
#  endif
#endif

#if !defined(BKSGE_CXX17_CONSTEXPR)
#  if defined(BKSGE_NO_CXX17_CONSTEXPR)
#    define BKSGE_CXX17_CONSTEXPR
#  else
#    define BKSGE_CXX17_CONSTEXPR constexpr
#  endif
#endif

#if !defined(BKSGE_CXX17_CONSTEXPR_OR_CONST)
#  if defined(BKSGE_NO_CXX17_CONSTEXPR)
#    define BKSGE_CXX17_CONSTEXPR_OR_CONST const
#  else
#    define BKSGE_CXX17_CONSTEXPR_OR_CONST constexpr
#  endif
#endif

#if !defined(BKSGE_STATIC_CONSTEXPR)
#  define BKSGE_STATIC_CONSTEXPR			static BKSGE_CONSTEXPR_OR_CONST
#endif

#if !defined(BKSGE_CXX14_STATIC_CONSTEXPR)
#  define BKSGE_CXX14_STATIC_CONSTEXPR		static BKSGE_CXX14_CONSTEXPR_OR_CONST
#endif

#if !defined(BKSGE_CXX17_STATIC_CONSTEXPR)
#  define BKSGE_CXX17_STATIC_CONSTEXPR		static BKSGE_CXX17_CONSTEXPR_OR_CONST
#endif

#endif // BKSGE_CONFIG_SUFFIX_CONSTEXPR_HPP
