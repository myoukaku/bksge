/**
 *	@file	tuple_tail_inl.hpp
 *
 *	@brief	tuple_tail 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_TAIL_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_TAIL_INL_HPP

#include <bksge/fnd/tuple/tuple_tail.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple_tail_type.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename Tuple, typename Result, bksge::size_t N, bool = (N > 1)>
struct tuple_tail_impl
{
	static BKSGE_CONSTEXPR Result
	invoke(Tuple&& t)
	{
		return do_tuple_tail(
			bksge::forward<Tuple>(t),
			bksge::make_index_sequence<N>());
	}

private:
	template <bksge::size_t I, bksge::size_t ... Indices>
	static BKSGE_CONSTEXPR Result
	do_tuple_tail(Tuple&& t, bksge::index_sequence<I, Indices...>)
	{
		return bksge::make_tuple(bksge::get<Indices>(bksge::forward<Tuple>(t))...);
	}
};

template <typename Tuple, typename Result, bksge::size_t N>
struct tuple_tail_impl<Tuple, Result, N, false>
{
	static BKSGE_CONSTEXPR Result
	invoke(Tuple&&)
	{
		return Result{};
	}
};

}	// namespace detail

template <typename Tuple>
inline BKSGE_CONSTEXPR tuple_tail_type_t<bksge::decay_t<Tuple>>
tuple_tail(Tuple&& t)
{
	return detail::tuple_tail_impl<
		Tuple,
		tuple_tail_type_t<bksge::decay_t<Tuple>>,
		bksge::tuple_size<bksge::decay_t<Tuple>>::value
	>::invoke(bksge::forward<Tuple>(t));
}

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_TAIL_INL_HPP
