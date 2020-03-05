/**
 *	@file	tuple_head.hpp
 *
 *	@brief	tuple_head 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_HEAD_HPP
#define BKSGE_FND_TUPLE_TUPLE_HEAD_HPP

#include <bksge/fnd/tuple/tuple_head_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Tuple>
BKSGE_CONSTEXPR tuple_head_type_t<bksge::decay_t<Tuple>>
tuple_head(Tuple&& t);

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_head_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_HEAD_HPP
