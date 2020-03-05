/**
 *	@file	tuple_last.hpp
 *
 *	@brief	tuple_last 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_LAST_HPP
#define BKSGE_FND_TUPLE_TUPLE_LAST_HPP

#include <bksge/fnd/tuple/tuple_last_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Tuple>
BKSGE_CONSTEXPR tuple_last_type_t<bksge::decay_t<Tuple>>
tuple_last(Tuple&& t);

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_last_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_LAST_HPP
