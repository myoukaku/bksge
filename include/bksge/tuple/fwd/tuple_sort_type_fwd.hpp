/**
 *	@file	tuple_sort_type_fwd.hpp
 *
 *	@brief	tuple_sort_type の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TUPLE_FWD_TUPLE_SORT_TYPE_FWD_HPP
#define BKSGE_TUPLE_FWD_TUPLE_SORT_TYPE_FWD_HPP

namespace bksge
{

struct value_less;

template <typename Tuple, typename Compare = value_less>
struct tuple_sort_type;

template <typename Tuple, typename Compare = value_less>
using tuple_sort_type_t = typename tuple_sort_type<Tuple, Compare>::type;

}	// namespace bksge

#endif // BKSGE_TUPLE_FWD_TUPLE_SORT_TYPE_FWD_HPP
