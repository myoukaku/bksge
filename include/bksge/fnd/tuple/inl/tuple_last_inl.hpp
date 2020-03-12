/**
 *	@file	tuple_last_inl.hpp
 *
 *	@brief	tuple_last 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_LAST_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_LAST_INL_HPP

#include <bksge/fnd/tuple/tuple_last.hpp>
#include <bksge/fnd/tuple/tuple_last_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>

namespace bksge
{

template <typename Tuple>
inline BKSGE_CONSTEXPR tuple_last_type_t<bksge::decay_t<Tuple>>
tuple_last(Tuple&& t)
{
	return std::get<
		std::tuple_size<bksge::decay_t<Tuple>>::value - 1
	>(bksge::forward<Tuple>(t));
}

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_LAST_INL_HPP
