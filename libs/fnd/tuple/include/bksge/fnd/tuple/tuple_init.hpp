/**
 *	@file	tuple_init.hpp
 *
 *	@brief	tuple_init 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_INIT_HPP
#define BKSGE_FND_TUPLE_TUPLE_INIT_HPP

#include <bksge/fnd/tuple/tuple_init_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Tuple>
BKSGE_CONSTEXPR tuple_init_type_t<bksge::decay_t<Tuple>>
tuple_init(Tuple&& t);

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_init_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_INIT_HPP
