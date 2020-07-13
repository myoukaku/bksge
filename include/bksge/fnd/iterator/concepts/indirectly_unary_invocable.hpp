/**
 *	@file	indirectly_unary_invocable.hpp
 *
 *	@brief	indirectly_unary_invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename I>
concept indirectly_unary_invocable =
	bksge::indirectly_readable<I> &&
	bksge::copy_constructible<F> &&
	bksge::invocable<F&, bksge::iter_value_t<I>&> &&
	bksge::invocable<F&, bksge::iter_reference_t<I>> &&
	bksge::invocable<F&, bksge::iter_common_reference_t<I>> &&
	bksge::common_reference_with<
		bksge::invoke_result_t<F&, bksge::iter_value_t<I>&>,
		bksge::invoke_result_t<F&, bksge::iter_reference_t<I>>
	>;

#endif

namespace detail
{

template <typename F, typename I>
struct indirectly_unary_invocable_t_impl
{
private:
	template <typename F2, typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::indirectly_readable_t<I2>,
		bksge::copy_constructible_t<F2>,
		bksge::invocable_t<F2&, bksge::iter_value_t<I2>&>,
		bksge::invocable_t<F2&, bksge::iter_reference_t<I2>>,
		bksge::invocable_t<F2&, bksge::iter_common_reference_t<I2>>,
		bksge::common_reference_with_t<
			bksge::invoke_result_t<F2&, bksge::iter_value_t<I2>&>,
			bksge::invoke_result_t<F2&, bksge::iter_reference_t<I2>>
		>
	>;

	template <typename F2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirectly_unary_invocable_t =
	typename detail::indirectly_unary_invocable_t_impl<F, I>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_UNARY_INVOCABLE_HPP
