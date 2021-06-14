/**
 *	@file	indirect_binary_predicate.hpp
 *
 *	@brief	indirect_binary_predicate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/predicate.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename I1, typename I2>
concept indirect_binary_predicate =
	bksge::indirectly_readable<I1> &&
	bksge::indirectly_readable<I2> &&
	bksge::copy_constructible<F> &&
	bksge::predicate<F&, bksge::iter_value_t<I1>&, bksge::iter_value_t<I2>&> &&
	bksge::predicate<F&, bksge::iter_value_t<I1>&, bksge::iter_reference_t<I2>> &&
	bksge::predicate<F&, bksge::iter_reference_t<I1>, bksge::iter_value_t<I2>&> &&
	bksge::predicate<F&, bksge::iter_reference_t<I1>, bksge::iter_reference_t<I2>> &&
	bksge::predicate<F&, bksge::iter_common_reference_t<I1>, bksge::iter_common_reference_t<I2>>;

#else

namespace detail
{

template <typename F, typename I1, typename I2>
struct indirect_binary_predicate_impl
{
private:
	template <typename F2, typename J1, typename J2,
		typename = bksge::enable_if_t<bksge::indirectly_readable<J1>::value>,
		typename = bksge::enable_if_t<bksge::indirectly_readable<J2>::value>,
		typename = bksge::enable_if_t<bksge::copy_constructible<F2>::value>,
		typename V1 = bksge::iter_value_t<J1>,
		typename V2 = bksge::iter_value_t<J2>,
		typename R1 = bksge::iter_reference_t<J1>,
		typename R2 = bksge::iter_reference_t<J2>,
		typename C1 = bksge::iter_common_reference_t<J1>,
		typename C2 = bksge::iter_common_reference_t<J2>,
		typename = bksge::enable_if_t<bksge::predicate<F2&, V1&, V2&>::value>,
		typename = bksge::enable_if_t<bksge::predicate<F2&, V1&, R2 >::value>,
		typename = bksge::enable_if_t<bksge::predicate<F2&, R1,  V2&>::value>,
		typename = bksge::enable_if_t<bksge::predicate<F2&, R1,  R2 >::value>,
		typename = bksge::enable_if_t<bksge::predicate<F2&, C1,  C2 >::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename F2, typename J1, typename J2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I1, I2>(0));
};

}	// namespace detail

template <typename F, typename I1, typename I2>
using indirect_binary_predicate =
	typename detail::indirect_binary_predicate_impl<F, I1, I2>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP
