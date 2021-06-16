/**
 *	@file	tuple_tail.hpp
 *
 *	@brief	tuple_tail 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_TAIL_HPP
#define BKSGE_FND_TUPLE_TUPLE_TAIL_HPP

#include <bksge/fnd/tuple/tuple_tail_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Tuple>
BKSGE_CONSTEXPR tuple_tail_type_t<bksge::decay_t<Tuple>>
tuple_tail(Tuple&& t);

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_tail_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_TAIL_HPP
