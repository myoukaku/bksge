/**
 *	@file	permutable.hpp
 *
 *	@brief	permutable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_PERMUTABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_PERMUTABLE_HPP

#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_movable_storable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept permutable =
	bksge::forward_iterator<Iter> &&
	bksge::indirectly_movable_storable<Iter, Iter> &&
	bksge::indirectly_swappable<Iter, Iter>;

#endif

namespace detail
{

template <typename Iter>
struct permutable_t_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::forward_iterator_t<I2>,
		bksge::indirectly_movable_storable_t<I2, I2>,
		bksge::indirectly_swappable_t<I2, I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using permutable_t =
	typename detail::permutable_t_impl<Iter>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_PERMUTABLE_HPP
