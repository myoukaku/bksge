/**
 *	@file	moment_of_inertia.hpp
 *
 *	@brief	moment_of_inertia の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MOMENT_OF_INERTIA_HPP
#define BKSGE_FND_UNITS_MOMENT_OF_INERTIA_HPP

#include <bksge/fnd/units/gram.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// キログラム平方メートル(慣性モーメントの単位)
template <typename T> using kilogram_square_metre  = decltype(kilogram<T>() * metre<T>() * metre<T>());
template <typename T> using kilogram_square_meter  = kilogram_square_metre<T>;
template <typename T> using kilograms_square_metre = kilogram_square_metre<T>;
template <typename T> using kilograms_square_meter = kilogram_square_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MOMENT_OF_INERTIA_HPP
