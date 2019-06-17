/**
 *	@file	pascal.hpp
 *
 *	@brief	pascal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_PASCAL_HPP
#define BKSGE_UNITS_PASCAL_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/newton.hpp>
#include <bksge/units/area.hpp>

namespace bksge
{

namespace units
{

// パスカル
template <typename T> using pascals = decltype(newton<T>() / square_metre<T>());
BKSGE_UNITS_SI_PREFIX(pascals);

// "pascal"がキーワードになっている環境では"pascal"は定義しない("pascals"を使う)
#if defined(_MSC_VER)
	#define BKSGE_UNITS_NO_PASCAL
#elif defined(pascal)
	#define BKSGE_UNITS_NO_PASCAL
#endif

#if !defined(BKSGE_UNITS_NO_PASCAL)
template <typename T> using pascal = pascals<T>;
BKSGE_UNITS_SI_PREFIX(pascal);
#endif

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_PASCAL_HPP
