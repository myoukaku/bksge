/**
 *	@file	weakly_incrementable.hpp
 *
 *	@brief	weakly_incrementable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/ranges/detail/signed_integer_like.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept weakly_incrementable =
	bksge::default_initializable<Iter> &&
	bksge::movable<Iter> &&
	requires(Iter i)
	{
		typename bksge::iter_difference_t<Iter>;
		requires bksge::ranges::detail::signed_integer_like<bksge::iter_difference_t<Iter>>;
		{ ++i } -> bksge::same_as<Iter&>;
		i++;
	};

template <typename Iter>
using is_weakly_incrementable = bksge::bool_constant<weakly_incrementable<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct weakly_incrementable_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<bksge::default_initializable<I2>::value>,
		typename = bksge::enable_if_t<bksge::movable<I2>::value>,
		typename D = bksge::iter_difference_t<I2>,
		typename = bksge::enable_if_t<bksge::ranges::detail::signed_integer_like<D>::value>,
		typename T = decltype(++std::declval<I2&>()),
		typename = bksge::enable_if_t<bksge::same_as<T, I2&>::value>,
		typename = decltype(std::declval<I2&>()++)
	>
	static auto test(int) -> bksge::true_type;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using weakly_incrementable =
	typename detail::weakly_incrementable_impl<Iter>::type;

template <typename Iter>
using is_weakly_incrementable = weakly_incrementable<Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP
