/**
 *	@file	predicate.hpp
 *
 *	@brief	predicate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_PREDICATE_HPP
#define BKSGE_FND_CONCEPTS_PREDICATE_HPP

#include <bksge/fnd/concepts/regular_invocable.hpp>
#include <bksge/fnd/concepts/detail/boolean_testable.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept predicate =
	bksge::regular_invocable<Fn, Args...> &&
	detail::boolean_testable<bksge::invoke_result_t<Fn, Args...>>;

#else

namespace detail
{

template <typename Fn, typename... Args>
struct predicate_impl
{
private:
	template <typename U, typename... As>
	static auto test(int) -> bksge::conjunction<
		bksge::regular_invocable<U, As...>,
		detail::boolean_testable<bksge::invoke_result_t<U, As...>>
	>;

	template <typename U, typename... As>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Fn, Args...>(0));
};

}	// namespace detail

template <typename Fn, typename... Args>
using predicate = typename detail::predicate_impl<Fn, Args...>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_PREDICATE_HPP
