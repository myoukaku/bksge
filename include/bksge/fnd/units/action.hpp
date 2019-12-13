/**
 *	@file	action.hpp
 *
 *	@brief	action の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ACTION_HPP
#define BKSGE_FND_UNITS_ACTION_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ジュール秒(作用の単位)
template <typename T> using joule_second  = decltype(joule<T>() * second<T>());
template <typename T> using joule_seconds = joule_second<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ACTION_HPP
