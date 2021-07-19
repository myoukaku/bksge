/**
 *	@file	tuple_head_inl.hpp
 *
 *	@brief	tuple_head 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_HEAD_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_HEAD_INL_HPP

#include <bksge/fnd/tuple/tuple_head.hpp>
#include <bksge/fnd/tuple/tuple_head_type.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <typename Tuple>
inline BKSGE_CONSTEXPR tuple_head_type_t<bksge::decay_t<Tuple>>
tuple_head(Tuple&& t)
{
	using std::get;
	return get<0>(std::forward<Tuple>(t));
}

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_HEAD_INL_HPP
