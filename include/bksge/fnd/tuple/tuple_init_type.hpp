/**
 *	@file	tuple_init_type.hpp
 *
 *	@brief	tuple_init_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_INIT_TYPE_HPP
#define BKSGE_FND_TUPLE_TUPLE_INIT_TYPE_HPP

#include <bksge/fnd/tuple/fwd/tuple_init_type_fwd.hpp>

namespace bksge
{

/**
 *	@brief	最終要素を除いたTupleを返す
 */
template <typename Tuple>
struct tuple_init_type;

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_init_type_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_INIT_TYPE_HPP
