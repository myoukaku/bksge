/**
 *	@file	tonne.hpp
 *
 *	@brief	tonne の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_TONNE_HPP
#define BKSGE_FND_UNITS_TONNE_HPP

#include <bksge/fnd/units/gram.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// トン(メトリックトン) = 1000kg
template <typename T> using tonne  = decltype(kilogram<T>() * bksge::ratio<1000>());
template <typename T> using tonnes = tonne<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_TONNE_HPP
