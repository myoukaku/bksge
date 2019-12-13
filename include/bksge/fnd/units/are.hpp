/**
 *	@file	are.hpp
 *
 *	@brief	are の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ARE_HPP
#define BKSGE_FND_UNITS_ARE_HPP

#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// アール(100 平方メートル)
template <typename T> using are  = decltype(decametre<T>() * decametre<T>());
template <typename T> using ares = are<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ARE_HPP
