/**
 *	@file	indirectly_comparable.hpp
 *
 *	@brief	indirectly_comparable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP

#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <
	typename I1,
	typename I2,
	typename Rel,
	typename P1 = bksge::identity,
	typename P2 = bksge::identity
>
concept indirectly_comparable =
	bksge::indirect_binary_predicate<Rel, bksge::projected<I1, P1>, bksge::projected<I2, P2>>;

#else

namespace detail
{

template <typename I1, typename I2, typename Rel, typename P1, typename P2>
struct indirectly_comparable_impl
{
private:
	template <typename J1, typename J2, typename R2, typename Q1, typename Q2>
	static auto test(int) -> bksge::indirect_binary_predicate<
		R2, bksge::projected<J1, Q1>, bksge::projected<J2, Q2>>;

	template <typename J1, typename J2, typename R2, typename Q1, typename Q2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<I1, I2, Rel, P1, P2>(0));
};

}	// namespace detail

template <
	typename I1,
	typename I2,
	typename Rel,
	typename P1 = bksge::identity,
	typename P2 = bksge::identity
>
using indirectly_comparable =
	typename detail::indirectly_comparable_impl<I1, I2, Rel, P1, P2>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_COMPARABLE_HPP
