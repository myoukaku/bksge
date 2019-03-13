/**
 *	@file	noexcept.hpp
 *
 *	@brief	BKSGE_NOEXCEPT の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_NOEXCEPT_HPP
#define BKSGE_CONFIG_SUFFIX_NOEXCEPT_HPP

//
// noexcept workarounds
//
#if !defined(BKSGE_NOEXCEPT)
#	if defined(BKSGE_NO_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT
#	else
#	  define BKSGE_NOEXCEPT noexcept
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_OR_NOTHROW)
#	if defined(BKSGE_NO_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_OR_NOTHROW throw()
#	else
#	  define BKSGE_NOEXCEPT_OR_NOTHROW noexcept
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_IF)
#	if defined(BKSGE_NO_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_IF(Predicate)
#	else
#	  define BKSGE_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_EXPR)
#	if defined(BKSGE_NO_CXX11_NOEXCEPT)
#	  define BKSGE_NOEXCEPT_EXPR(Expression) false
#	else
#	  define BKSGE_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#	endif
#endif

#if !defined(BKSGE_NOEXCEPT_IF_EXPR)
#	define BKSGE_NOEXCEPT_IF_EXPR(Expression)	BKSGE_NOEXCEPT_IF(BKSGE_NOEXCEPT_EXPR((Expression)))
#endif

#endif // BKSGE_CONFIG_SUFFIX_NOEXCEPT_HPP
