/**
 *	@file	pound.hpp
 *
 *	@brief	pound の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_POUND_HPP
#define BKSGE_FND_UNITS_POUND_HPP

#include <bksge/fnd/units/gram.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 常用ポンド(正確に0.45359237キログラム)
template <typename T> using pound  = decltype(gram<T>() * std::ratio<45359237LL, 100000LL>());
template <typename T> using pounds = pound<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_POUND_HPP
