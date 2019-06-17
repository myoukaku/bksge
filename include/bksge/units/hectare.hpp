/**
 *	@file	hectare.hpp
 *
 *	@brief	hectare の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_HECTARE_HPP
#define BKSGE_UNITS_HECTARE_HPP

#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// ヘクタール(10,000 平方メートル)
template <typename T> using hectare  = decltype(hectometre<T>() * hectometre<T>());
template <typename T> using hectares = hectare<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_HECTARE_HPP
