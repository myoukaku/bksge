/**
 *	@file	constexpr.hpp
 *
 *	@brief	BKSGE_CONSTEXPR の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_CONSTEXPR_HPP
#define BKSGE_FND_CONFIG_SUFFIX_CONSTEXPR_HPP

//
// constexpr workarounds
//
#if !defined(BKSGE_CONSTEXPR)
#  if defined(BKSGE_HAS_CXX11_CONSTEXPR)
#    define BKSGE_CONSTEXPR constexpr
#  else
#    define BKSGE_CONSTEXPR
#  endif
#endif

#if !defined(BKSGE_CONSTEXPR_OR_CONST)
# if defined(BKSGE_HAS_CXX11_CONSTEXPR)
#   define BKSGE_CONSTEXPR_OR_CONST constexpr
# else
#   define BKSGE_CONSTEXPR_OR_CONST const
# endif
#endif

#if !defined(BKSGE_CXX14_CONSTEXPR)
#  if defined(BKSGE_HAS_CXX14_CONSTEXPR)
#    define BKSGE_CXX14_CONSTEXPR constexpr
#  else
#    define BKSGE_CXX14_CONSTEXPR
#  endif
#endif

#if !defined(BKSGE_CXX14_CONSTEXPR_OR_CONST)
#  if defined(BKSGE_HAS_CXX14_CONSTEXPR)
#    define BKSGE_CXX14_CONSTEXPR_OR_CONST constexpr
#  else
#    define BKSGE_CXX14_CONSTEXPR_OR_CONST const
#  endif
#endif

#if !defined(BKSGE_CXX17_CONSTEXPR)
#  if defined(BKSGE_HAS_CXX17_CONSTEXPR)
#    define BKSGE_CXX17_CONSTEXPR constexpr
#  else
#    define BKSGE_CXX17_CONSTEXPR
#  endif
#endif

#if !defined(BKSGE_CXX17_CONSTEXPR_OR_CONST)
#  if defined(BKSGE_HAS_CXX17_CONSTEXPR)
#    define BKSGE_CXX17_CONSTEXPR_OR_CONST constexpr
#  else
#    define BKSGE_CXX17_CONSTEXPR_OR_CONST const
#  endif
#endif

#if !defined(BKSGE_CXX20_CONSTEXPR)
#  if defined(BKSGE_HAS_CXX20_CONSTEXPR)
#    define BKSGE_CXX20_CONSTEXPR constexpr
#  else
#    define BKSGE_CXX20_CONSTEXPR
#  endif
#endif

#if !defined(BKSGE_CXX20_CONSTEXPR_OR_CONST)
#  if defined(BKSGE_HAS_CXX20_CONSTEXPR)
#    define BKSGE_CXX20_CONSTEXPR_OR_CONST constexpr
#  else
#    define BKSGE_CXX20_CONSTEXPR_OR_CONST const
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

#if !defined(BKSGE_CXX20_STATIC_CONSTEXPR)
#  define BKSGE_CXX20_STATIC_CONSTEXPR		static BKSGE_CXX20_CONSTEXPR_OR_CONST
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_CONSTEXPR_HPP
