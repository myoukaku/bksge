/**
 *	@file	nth_inl.hpp
 *
 *	@brief	nth の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_NTH_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_NTH_INL_HPP

#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/index_sequence_for.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

// 単純な再帰での実装
// 再帰深度はO(N)
#if 0
template <typename Head, typename... Tail>
struct nth<0, Head, Tail...>
{
	using type = Head;
};

template <bksge::size_t N, typename Head, typename... Tail>
struct nth<N, Head, Tail...>
	: public nth<N - 1, Tail...>
{};
#endif

// "void* trick" を使った実装。
// 再帰深度はO(logN)
#if 0
namespace nth_detail
{

template <typename Seq>
struct nth_impl;

template <bksge::size_t... Indices>
struct nth_impl<bksge::index_sequence<Indices...>>
{
	template <bksge::size_t>
	struct void_ptr
	{
		using type = void*;
	};

	template <typename T>
	static T eval(typename void_ptr<Indices>::type..., T*, ...);
};

}	// namespace nth_detail

template <bksge::size_t I, typename... Types>
struct nth
{
private:
	using Seq = bksge::make_index_sequence<I>;

	// MSVC12 で decltype()::type ができないので、一時的な型で受ける
	using tmp_type = decltype(
		nth_detail::nth_impl<Seq>::eval(
			static_cast<bksge::type_identity<Types>*>(nullptr)...));
public:
	using type = typename tmp_type::type;
};
#endif

// 多重継承を使った実装
// 再帰深度はO(logN)
#if 1
namespace nth_detail
{

template <bksge::size_t N, typename T>
struct element_holder
	: public bksge::type_identity<T>
{};

template <typename Sequence, typename... Types>
struct type_tuple;

template <bksge::size_t... Indices, typename... Types>
struct type_tuple<bksge::index_sequence<Indices...>, Types...>
	: public element_holder<Indices, Types>...
{};

template <bksge::size_t N, typename T>
static element_holder<N, T> select(element_holder<N, T>);

template <bool, bksge::size_t N, typename... Types>
struct nth
{
private:
	using Seq = bksge::index_sequence_for<Types...>;
	using Tmp = decltype(select<N>(
		bksge::declval<type_tuple<Seq, Types...>>()));
public:
	using type = typename Tmp::type;
};

template <bksge::size_t N, typename... Types>
struct nth<false, N, Types...>
{};

}	// namespace nth_detail

template <bksge::size_t N, typename... Types>
struct nth : public nth_detail::nth<(N < sizeof...(Types)), N, Types...>
{};
#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_NTH_INL_HPP
