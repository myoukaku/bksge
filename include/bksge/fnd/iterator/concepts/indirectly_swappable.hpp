/**
 *	@file	indirectly_swappable.hpp
 *
 *	@brief	indirectly_swappable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_swap.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename I1, typename I2 = I1>
concept indirectly_swappable =
	bksge::indirectly_readable<I1> &&
	bksge::indirectly_readable<I2> &&
	requires(I1 const i1, I2 const i2)
	{
		bksge::ranges::iter_swap(i1, i1);
		bksge::ranges::iter_swap(i2, i2);
		bksge::ranges::iter_swap(i1, i2);
		bksge::ranges::iter_swap(i2, i1);
	};

#else

namespace detail
{

template <typename I1, typename I2>
struct indirectly_swappable_impl
{
private:
	template <typename J1, typename J2,
		typename = bksge::enable_if_t<
			bksge::conjunction<
				bksge::indirectly_readable<J1>,
				bksge::indirectly_readable<J2>
			>::value
		>
	>
	static auto test(int) -> decltype(
		bksge::ranges::iter_swap(bksge::declval<J1 const>(), bksge::declval<J1 const>()),
		bksge::ranges::iter_swap(bksge::declval<J1 const>(), bksge::declval<J2 const>()),
		bksge::ranges::iter_swap(bksge::declval<J2 const>(), bksge::declval<J1 const>()),
		bksge::ranges::iter_swap(bksge::declval<J2 const>(), bksge::declval<J2 const>()),
		bksge::true_type{}
	);

	template <typename J1, typename J2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<I1, I2>(0));
};

}	// namespace detail

template <typename I1, typename I2 = I1>
using indirectly_swappable =
	typename detail::indirectly_swappable_impl<I1, I2>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECTLY_SWAPPABLE_HPP
