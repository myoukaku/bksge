/**
 *	@file	tuple_count.hpp
 *
 *	@brief	tuple_count の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_COUNT_HPP
#define BKSGE_FND_TUPLE_TUPLE_COUNT_HPP

namespace bksge
{

/**
 *	@brief	Tupleの中にTが何回現れるかを返す
 */
template <typename T, typename Tuple>
struct tuple_count;

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_count_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_COUNT_HPP
