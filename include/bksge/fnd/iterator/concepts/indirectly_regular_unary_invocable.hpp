/**
 *	@file	indirectly_regular_unary_invocable.hpp
 *
 *	@brief	indirectly_regular_unary_invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/regular_invocable.hpp>
#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename I>
concept indirectly_regular_unary_invocable =
	bksge::indirectly_readable<I> &&
	bksge::copy_constructible<F> &&
	bksge::regular_invocable<F&, bksge::iter_value_t<I>&> &&
	bksge::regular_invocable<F&, bksge::iter_reference_t<I>> &&
	bksge::regular_invocable<F&, bksge::iter_common_reference_t<I>> &&
	bksge::common_reference_with<
		bksge::invoke_result_t<F&, bksge::iter_value_t<I>&>,
		bksge::invoke_result_t<F&, bksge::iter_reference_t<I>>
	>;

#else

namespace detail
{

template <typename F, typename I>
struct indirectly_regular_unary_invocable_impl
{
private:
	template <typename F2, typename I2,
		typename = bksge::enable_if_t<bksge::indirectly_readable<I2>::value>,
		typename = bksge::enable_if_t<bksge::copy_constructible<F2>::value>,
		typename V = bksge::iter_value_t<I2>,
		typename = bksge::enable_if_t<bksge::regular_invocable<F2&, V&>::value>,
		typename R = bksge::iter_reference_t<I2>,
		typename = bksge::enable_if_t<bksge::regular_invocable<F2&, R>::value>,
		typename C = bksge::iter_common_reference_t<I2>,
		typename = bksge::enable_if_t<bksge::regular_invocable<F2&, C>::value>,
		typename = bksge::enable_if_t<
			bksge::common_reference_with<
				bksge::invoke_result_t<F2&, V&>,
				bksge::invoke_result_t<F2&, R>
			>::value
		>
	>
	static auto test(int) -> bksge::true_type;

	template <typename F2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirectly_regular_unary_invocable =
	typename detail::indirectly_regular_unary_invocable_impl<F, I>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_REGULAR_UNARY_INVOCABLE_HPP
