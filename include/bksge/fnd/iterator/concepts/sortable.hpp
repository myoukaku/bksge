/**
 *	@file	sortable.hpp
 *
 *	@brief	sortable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_SORTABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_SORTABLE_HPP

#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <
	typename Iter,
	typename Rel = bksge::ranges::less,
	typename Proj = bksge::identity
>
concept sortable =
	bksge::permutable<Iter> &&
	bksge::indirect_strict_weak_order<Rel, bksge::projected<Iter, Proj>>;

#else

namespace detail
{

template <typename Iter, typename Rel, typename Proj>
struct sortable_impl
{
private:
	template <typename I, typename R, typename P>
	static auto test(int) -> bksge::conjunction<
		bksge::permutable<I>,
		bksge::indirect_strict_weak_order<R, bksge::projected<I, P>>
	>;

	template <typename I, typename R, typename P>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter, Rel, Proj>(0));
};

}	// namespace detail

template <
	typename Iter,
	typename Rel = bksge::ranges::less,
	typename Proj = bksge::identity
>
using sortable =
	typename detail::sortable_impl<Iter, Rel, Proj>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_SORTABLE_HPP
