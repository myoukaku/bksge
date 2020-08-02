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
#include <bksge/fnd/iterator/concepts/detail/is_signed_integer_like.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

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
		requires bksge::detail::is_signed_integer_like<bksge::iter_difference_t<Iter>>;
		{ ++i } -> bksge::same_as<Iter&>;
		i++;
	};

#else

namespace detail
{

template <typename Iter>
struct weakly_incrementable_impl
{
private:
	template <typename I2, typename = decltype(bksge::declval<I2&>()++)>
	static auto test(int) -> bksge::conjunction<
		bksge::default_initializable_t<I2>,
		bksge::movable_t<I2>,
		bksge::detail::is_signed_integer_like<bksge::iter_difference_t<I2>>,
		bksge::same_as_t<decltype(++bksge::declval<I2&>()), I2&>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using weakly_incrementable =
	typename detail::weakly_incrementable_impl<Iter>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_WEAKLY_INCREMENTABLE_HPP
