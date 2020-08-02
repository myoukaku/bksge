/**
 *	@file	indirect_result_t.hpp
 *
 *	@brief	indirect_result_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INDIRECT_RESULT_T_HPP
#define BKSGE_FND_ITERATOR_INDIRECT_RESULT_T_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename... Is>
requires
	(bksge::indirectly_readable<Is>&& ...) &&
	 bksge::invocable<F, bksge::iter_reference_t<Is>...>
using indirect_result_t = bksge::invoke_result_t<F, bksge::iter_reference_t<Is>...>;

#else

namespace detail
{

template <typename...>
struct type_pack
{};

// Visual Studio 2017 のバグに対応するため、2段階で解決する
template <typename, typename, typename = void>
struct indirect_result_t_impl_2;

template <typename F, typename... Is>
struct indirect_result_t_impl_2<F, type_pack<Is...>,
	bksge::enable_if_t<
		bksge::invocable_t<F, Is...>::value
	>
>
{
	using type = bksge::invoke_result_t<F, Is...>;
};

template <typename, typename, typename = void>
struct indirect_result_t_impl;

template <typename F, typename... Is>
struct indirect_result_t_impl<F, type_pack<Is...>,
	bksge::enable_if_t<
		bksge::conjunction<bksge::indirectly_readable<Is>...>::value
	>
> : public indirect_result_t_impl_2<F, type_pack<bksge::iter_reference_t<Is>...>> {};

}	// namespace detail

template <typename F, typename... Is>
using indirect_result_t = typename detail::indirect_result_t_impl<F, detail::type_pack<Is...>>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INDIRECT_RESULT_T_HPP
