/**
 *	@file	tuple_tail_type_fwd.hpp
 *
 *	@brief	tuple_tail_type の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_FWD_TUPLE_TAIL_TYPE_FWD_HPP
#define BKSGE_FND_TUPLE_FWD_TUPLE_TAIL_TYPE_FWD_HPP

namespace bksge
{

template <typename Tuple>
struct tuple_tail_type;

template <typename Tuple>
using tuple_tail_type_t = typename tuple_tail_type<Tuple>::type;

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_FWD_TUPLE_TAIL_TYPE_FWD_HPP
