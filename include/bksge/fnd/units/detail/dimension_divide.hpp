/**
 *	@file	dimension_divide.hpp
 *
 *	@brief	dimension_divide の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_DIMENSION_DIVIDE_HPP
#define BKSGE_FND_UNITS_DETAIL_DIMENSION_DIVIDE_HPP

#include <bksge/fnd/units/detail/dimension_multiply.hpp>
#include <bksge/fnd/units/detail/dimension_inverse.hpp>

namespace bksge
{

namespace units
{

/**
 *	@brief	derived_dimension同士を除算して新しいderived_dimensionを得る
 */
template <typename D1, typename D2>
using dimension_divide = dimension_multiply<D1, dimension_inverse<D2>>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_DIMENSION_DIVIDE_HPP
