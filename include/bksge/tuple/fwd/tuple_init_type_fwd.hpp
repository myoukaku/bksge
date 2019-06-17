/**
 *	@file	tuple_init_type_fwd.hpp
 *
 *	@brief	tuple_init_type の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TUPLE_FWD_TUPLE_INIT_TYPE_FWD_HPP
#define BKSGE_TUPLE_FWD_TUPLE_INIT_TYPE_FWD_HPP

namespace bksge
{

template <typename Tuple>
struct tuple_init_type;

template <typename Tuple>
using tuple_init_type_t = typename tuple_init_type<Tuple>::type;

}	// namespace bksge

#endif // BKSGE_TUPLE_FWD_TUPLE_INIT_TYPE_FWD_HPP
