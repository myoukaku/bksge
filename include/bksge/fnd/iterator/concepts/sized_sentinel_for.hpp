/**
 *	@file	sized_sentinel_for.hpp
 *
 *	@brief	sized_sentinel_for の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Sent, typename Iter>
concept sized_sentinel_for =
	bksge::sentinel_for<Sent, Iter> &&
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	!bksge::disable_sized_sentinel_for<bksge::remove_cv_t<Sent>, bksge::remove_cv_t<Iter>> &&
#else
	!bksge::disable_sized_sentinel_for<bksge::remove_cv_t<Sent>, bksge::remove_cv_t<Iter>>::value &&
#endif
	requires(const Iter& i, const Sent& s)
	{
		{ s - i } -> bksge::same_as<bksge::iter_difference_t<Iter>>;
		{ i - s } -> bksge::same_as<bksge::iter_difference_t<Iter>>;
	};

#else

namespace detail
{

template <typename Sent, typename Iter>
struct sized_sentinel_for_impl
{
private:
	template <typename S2, typename I2,
		typename D1 = decltype(bksge::declval<const S2&>() - bksge::declval<const I2&>()),
		typename D2 = decltype(bksge::declval<const I2&>() - bksge::declval<const S2&>()),
		typename = bksge::enable_if_t<
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
			!bksge::disable_sized_sentinel_for<bksge::remove_cv_t<S2>, bksge::remove_cv_t<I2>>
#else
			!bksge::disable_sized_sentinel_for<bksge::remove_cv_t<S2>, bksge::remove_cv_t<I2>>::value
#endif
		>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::sentinel_for<S2, I2>,
		bksge::same_as_t<D1, bksge::iter_difference_t<I2>>,
		bksge::same_as_t<D2, bksge::iter_difference_t<I2>>
	>;

	template <typename S2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Sent, Iter>(0));
};

}	// namespace detail

template <typename Sent, typename Iter>
using sized_sentinel_for =
	typename detail::sized_sentinel_for_impl<Sent, Iter>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
