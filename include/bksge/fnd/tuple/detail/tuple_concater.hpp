/**
 *	@file	tuple_concater.hpp
 *
 *	@brief	tuple_concater の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_TUPLE_CONCATER_HPP
#define BKSGE_FND_TUPLE_DETAIL_TUPLE_CONCATER_HPP

#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace tuple_detail
{

// Performs the actual concatenation by step-wise expanding tuple-like
// objects into the elements,  which are finally forwarded into the
// result tuple.
template <typename Ret, typename... Tuples>
struct tuple_concater;

template <typename Ret, typename T, typename... Tuples>
struct tuple_concater<Ret, T, Tuples...>
{
private:
	template <std::size_t... Indices, typename... Args>
	static BKSGE_CONSTEXPR Ret
	invoke_impl(bksge::index_sequence<Indices...>, T&& tp, Tuples&&... tps, Args&&... args)
	{
		using next = tuple_concater<Ret, Tuples...>;
		return next::invoke(
			bksge::forward<Tuples>(tps)...,
			bksge::forward<Args>(args)...,
			bksge::get<Indices>(bksge::forward<T>(tp))...);
	}

public:
	template <typename... Args>
	static BKSGE_CONSTEXPR Ret
	invoke(T&& tp, Tuples&&... tps, Args&&... args)
	{
		using IndexSeq = bksge::make_index_sequence<
			bksge::tuple_size<
				bksge::remove_reference_t<T>
			>::value>;
		return invoke_impl(
			IndexSeq{},
			bksge::forward<T>(tp),
			bksge::forward<Tuples>(tps)...,
			bksge::forward<Args>(args)...);
	}
};

template <typename Ret>
struct tuple_concater<Ret>
{
	template <typename... Args>
	static BKSGE_CONSTEXPR Ret
	invoke(Args&&... args)
	{
		return Ret(bksge::forward<Args>(args)...);
	}
};

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_TUPLE_CONCATER_HPP
