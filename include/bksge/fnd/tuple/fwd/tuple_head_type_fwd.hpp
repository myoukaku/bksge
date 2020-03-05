/**
 *	@file	tuple_head_type_fwd.hpp
 *
 *	@brief	tuple_head_type の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_FWD_TUPLE_HEAD_TYPE_FWD_HPP
#define BKSGE_FND_TUPLE_FWD_TUPLE_HEAD_TYPE_FWD_HPP

namespace bksge
{

template <typename Tuple>
struct tuple_head_type;

template <typename Tuple>
using tuple_head_type_t = typename tuple_head_type<Tuple>::type;

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_FWD_TUPLE_HEAD_TYPE_FWD_HPP
