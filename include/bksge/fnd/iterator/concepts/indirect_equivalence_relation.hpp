/**
 *	@file	indirect_equivalence_relation.hpp
 *
 *	@brief	indirect_equivalence_relation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_EQUIVALENCE_RELATION_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_EQUIVALENCE_RELATION_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/equivalence_relation.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename I1, typename I2 = I1>
concept indirect_equivalence_relation =
	bksge::indirectly_readable<I1> &&
	bksge::indirectly_readable<I2> &&
	bksge::copy_constructible<F> &&
	bksge::equivalence_relation<F&, bksge::iter_value_t<I1>&, bksge::iter_value_t<I2>&> &&
	bksge::equivalence_relation<F&, bksge::iter_value_t<I1>&, bksge::iter_reference_t<I2>> &&
	bksge::equivalence_relation<F&, bksge::iter_reference_t<I1>, bksge::iter_value_t<I2>&> &&
	bksge::equivalence_relation<F&, bksge::iter_reference_t<I1>, bksge::iter_reference_t<I2>> &&
	bksge::equivalence_relation<F&, bksge::iter_common_reference_t<I1>, bksge::iter_common_reference_t<I2>>;

#else

namespace detail
{

template <typename F, typename I1, typename I2>
struct indirect_equivalence_relation_impl
{
private:
	template <typename F2, typename J1, typename J2>
	static auto test(int) -> bksge::conjunction<
		bksge::indirectly_readable<J1>,
		bksge::indirectly_readable<J2>,
		bksge::copy_constructible<F2>,
		bksge::equivalence_relation<F2&, bksge::iter_value_t<J1>&, bksge::iter_value_t<J2>&>,
		bksge::equivalence_relation<F2&, bksge::iter_value_t<J1>&, bksge::iter_reference_t<J2>>,
		bksge::equivalence_relation<F2&, bksge::iter_reference_t<J1>, bksge::iter_value_t<J2>&>,
		bksge::equivalence_relation<F2&, bksge::iter_reference_t<J1>, bksge::iter_reference_t<J2>>,
		bksge::equivalence_relation<F2&, bksge::iter_common_reference_t<J1>, bksge::iter_common_reference_t<J2>>
	>;

	template <typename F2, typename J1, typename J2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I1, I2>(0));
};

}	// namespace detail

template <typename F, typename I1, typename I2 = I1>
using indirect_equivalence_relation =
	typename detail::indirect_equivalence_relation_impl<F, I1, I2>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_EQUIVALENCE_RELATION_HPP
