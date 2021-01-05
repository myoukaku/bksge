/**
 *	@file	quantity_fwd.hpp
 *
 *	@brief	quantity の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_QUANTITY_FWD_HPP
#define BKSGE_FND_UNITS_DETAIL_QUANTITY_FWD_HPP

#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

template <typename T, typename Dimension, typename Scale = bksge::ratio<1>, typename Offset = bksge::ratio<0>>
class quantity;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_QUANTITY_FWD_HPP
