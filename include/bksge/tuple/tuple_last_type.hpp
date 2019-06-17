/**
 *	@file	tuple_last_type.hpp
 *
 *	@brief	tuple_last_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TUPLE_TUPLE_LAST_TYPE_HPP
#define BKSGE_TUPLE_TUPLE_LAST_TYPE_HPP

#include <bksge/tuple/fwd/tuple_last_type_fwd.hpp>

namespace bksge
{

/**
 *	@brief	Tupleの最終要素の型を返す
 */
template <typename Tuple>
struct tuple_last_type;

}	// namespace bksge

#include <bksge/tuple/inl/tuple_last_type_inl.hpp>

#endif // BKSGE_TUPLE_TUPLE_LAST_TYPE_HPP
