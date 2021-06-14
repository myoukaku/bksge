/**
 *	@file	radix_sortable.hpp
 *
 *	@brief	ranges::detail::radix_sortable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_DETAIL_RADIX_SORTABLE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_DETAIL_RADIX_SORTABLE_HPP

#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <
	typename Iter,
	typename Proj = bksge::identity
>
concept radix_sortable =
	bksge::permutable<Iter> &&
	bksge::unsigned_integral<
		bksge::iter_value_t<bksge::projected<Iter, Proj>>
	>;

#else

template <typename Iter, typename Proj>
struct radix_sortable_impl
{
private:
	template <typename I, typename P,
		typename = bksge::enable_if_t<bksge::permutable<I>::value>,
		typename = bksge::enable_if_t<
			bksge::unsigned_integral<
				bksge::iter_value_t<bksge::projected<I, P>>
			>::value
		>
	>
	static auto test(int) -> bksge::true_type;

	template <typename I, typename P>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter, Proj>(0));
};

template <
	typename Iter,
	typename Proj = bksge::identity
>
using radix_sortable =
	typename detail::radix_sortable_impl<Iter, Proj>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_DETAIL_RADIX_SORTABLE_HPP
