/**
 *	@file	mergeable.hpp
 *
 *	@brief	mergeable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_MERGEABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_MERGEABLE_HPP

#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <
	typename I1,
	typename I2,
	typename Out,
	typename Rel = bksge::ranges::less,
	typename P1 = bksge::identity,
	typename P2 = bksge::identity
>
concept mergeable =
	bksge::input_iterator<I1> &&
	bksge::input_iterator<I2> &&
	bksge::weakly_incrementable<Out> &&
	bksge::indirectly_copyable<I1, Out> &&
	bksge::indirectly_copyable<I2, Out> &&
	bksge::indirect_strict_weak_order<Rel, bksge::projected<I1, P1>, bksge::projected<I2, P2>>;

#else

namespace detail
{

template <typename I1, typename I2, typename Out, typename Rel, typename P1, typename P2>
struct mergeable_impl
{
private:
	template <typename J1, typename J2, typename O2, typename R2, typename Q1, typename Q2,
		typename = bksge::enable_if_t<bksge::input_iterator<J1>::value>,
		typename = bksge::enable_if_t<bksge::input_iterator<J2>::value>,
		typename = bksge::enable_if_t<bksge::weakly_incrementable<O2>::value>,
		typename = bksge::enable_if_t<bksge::indirectly_copyable<J1, O2>::value>,
		typename = bksge::enable_if_t<bksge::indirectly_copyable<J2, O2>::value>,
		typename = bksge::enable_if_t<bksge::indirect_strict_weak_order<
			R2, bksge::projected<J1, Q1>, bksge::projected<J2, Q2>>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename J1, typename J2, typename O2, typename R2, typename Q1, typename Q2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<I1, I2, Out, Rel, P1, P2>(0));
};

}	// namespace detail

template <
	typename I1,
	typename I2,
	typename Out,
	typename Rel = bksge::ranges::less,
	typename P1 = bksge::identity,
	typename P2 = bksge::identity
>
using mergeable =
	typename detail::mergeable_impl<I1, I2, Out, Rel, P1, P2>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_MERGEABLE_HPP
