/**
 *	@file	noexcept.hpp
 *
 *	@brief	BKSGE_NOEXCEPT の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_NOEXCEPT_HPP
#define BKSGE_FND_CONFIG_SUFFIX_NOEXCEPT_HPP

//
// noexcept workarounds
//
#if !defined(BKSGE_NOEXCEPT)
#	if defined(BKSGE_HAS_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT noexcept
#	else
#	  define BKSGE_NOEXCEPT
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_OR_NOTHROW)
#	if defined(BKSGE_HAS_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_OR_NOTHROW noexcept
#	else
#	  define BKSGE_NOEXCEPT_OR_NOTHROW throw()
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_IF)
#	if defined(BKSGE_HAS_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#	else
#	  define BKSGE_NOEXCEPT_IF(Predicate)
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_EXPR)
#	if defined(BKSGE_HAS_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#	else
#	  define BKSGE_NOEXCEPT_EXPR(Expression) false
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_IF_EXPR)
#	define BKSGE_NOEXCEPT_IF_EXPR(Expression)	BKSGE_NOEXCEPT_IF(BKSGE_NOEXCEPT_EXPR((Expression)))
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_NOEXCEPT_HPP
