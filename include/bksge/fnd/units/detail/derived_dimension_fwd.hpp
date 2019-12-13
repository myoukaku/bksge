/**
 *	@file	derived_dimension_fwd.hpp
 *
 *	@brief	derived_dimension の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_FWD_HPP
#define BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_FWD_HPP

namespace bksge
{

namespace units
{

template <typename Dimension, int Power = 1>
struct dimension_holder;

template <typename... BaseDimensions>
struct derived_dimension;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_FWD_HPP
