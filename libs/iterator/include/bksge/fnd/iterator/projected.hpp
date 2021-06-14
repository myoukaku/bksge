/**
 *	@file	projected.hpp
 *
 *	@brief	projected の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_PROJECTED_HPP
#define BKSGE_FND_ITERATOR_PROJECTED_HPP

#include <bksge/fnd/iterator/indirect_result_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_regular_unary_invocable.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::indirectly_readable I,
	bksge::indirectly_regular_unary_invocable<I> Proj
#else
	typename I,
	typename Proj,
	typename = bksge::enable_if_t<
		bksge::indirectly_readable<I>::value &&
		bksge::indirectly_regular_unary_invocable<Proj, I>::value
	>
#endif
>
struct projected
{
	using value_type = bksge::remove_cvref_t<bksge::indirect_result_t<Proj&, I>>;

	bksge::indirect_result_t<Proj&, I> operator*() const; // not defined
};

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::weakly_incrementable I,
#else
	typename I,
#endif
	typename Proj
>
struct incrementable_traits<projected<I, Proj>>
{
	using difference_type = bksge::iter_difference_t<I>;
};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_PROJECTED_HPP
