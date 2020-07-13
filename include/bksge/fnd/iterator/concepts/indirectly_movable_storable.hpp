/**
 *	@file	indirectly_movable_storable.hpp
 *
 *	@brief	indirectly_movable_storable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_STORABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_STORABLE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_movable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename In, typename Out>
concept indirectly_movable_storable =
	bksge::indirectly_movable<In, Out> &&
	bksge::indirectly_writable<Out, bksge::iter_value_t<In>> &&
	bksge::movable<bksge::iter_value_t<In>> &&
	bksge::constructible_from<bksge::iter_value_t<In>, bksge::iter_rvalue_reference_t<In>> &&
	bksge::assignable_from<bksge::iter_value_t<In>&, bksge::iter_rvalue_reference_t<In>>;

#endif

namespace detail
{

template <typename In, typename Out>
struct indirectly_movable_storable_t_impl
{
private:
	template <typename I, typename O>
	static auto test(int) -> bksge::conjunction<
		bksge::indirectly_movable_t<I, O>,
		bksge::indirectly_writable_t<O, bksge::iter_value_t<I>>,
		bksge::movable_t<bksge::iter_value_t<I>>,
		bksge::constructible_from_t<bksge::iter_value_t<I>, bksge::iter_rvalue_reference_t<I>>,
		bksge::assignable_from_t<bksge::iter_value_t<I>&, bksge::iter_rvalue_reference_t<I>>
	>;

	template <typename I, typename O>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<In, Out>(0));
};

}	// namespace detail

template <typename In, typename Out>
using indirectly_movable_storable_t =
	typename detail::indirectly_movable_storable_t_impl<In, Out>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_MOVABLE_STORABLE_HPP
