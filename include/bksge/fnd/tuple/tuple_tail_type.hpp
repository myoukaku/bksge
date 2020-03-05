/**
 *	@file	tuple_tail_type.hpp
 *
 *	@brief	tuple_tail_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_TAIL_TYPE_HPP
#define BKSGE_FND_TUPLE_TUPLE_TAIL_TYPE_HPP

#include <bksge/fnd/tuple/fwd/tuple_tail_type_fwd.hpp>

namespace bksge
{

/**
 *	@brief	先頭要素を除いたTupleを返す
 */
template <typename Tuple>
struct tuple_tail_type;

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_tail_type_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_TAIL_TYPE_HPP
