/**
 *	@file	tuple_last_type_fwd.hpp
 *
 *	@brief	tuple_last_type の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_FWD_TUPLE_LAST_TYPE_FWD_HPP
#define BKSGE_FND_TUPLE_FWD_TUPLE_LAST_TYPE_FWD_HPP

namespace bksge
{

template <typename Tuple>
struct tuple_last_type;

template <typename Tuple>
using tuple_last_type_t = typename tuple_last_type<Tuple>::type;

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_FWD_TUPLE_LAST_TYPE_FWD_HPP
