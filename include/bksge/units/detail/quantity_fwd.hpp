/**
 *	@file	quantity_fwd.hpp
 *
 *	@brief	quantity の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DETAIL_QUANTITY_FWD_HPP
#define BKSGE_UNITS_DETAIL_QUANTITY_FWD_HPP

#include <ratio>

namespace bksge
{

namespace units
{

template <typename T, typename Dimension, typename Scale = std::ratio<1>, typename Offset = std::ratio<0>>
class quantity;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_DETAIL_QUANTITY_FWD_HPP
