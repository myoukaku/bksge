/**
 *	@file	tuple_head_type.hpp
 *
 *	@brief	tuple_head_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_HEAD_TYPE_HPP
#define BKSGE_FND_TUPLE_TUPLE_HEAD_TYPE_HPP

#include <bksge/fnd/tuple/fwd/tuple_head_type_fwd.hpp>

namespace bksge
{

/**
 *	@brief	Tupleの先頭要素の型を返す
 */
template <typename Tuple>
struct tuple_head_type;

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_head_type_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_HEAD_TYPE_HPP
