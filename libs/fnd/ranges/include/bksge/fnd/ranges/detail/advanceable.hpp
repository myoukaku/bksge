/**
 *	@file	advanceable.hpp
 *
 *	@brief	advanceable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_ADVANCEABLE_HPP
#define BKSGE_FND_RANGES_DETAIL_ADVANCEABLE_HPP

#include <bksge/fnd/ranges/detail/decrementable.hpp>
#include <bksge/fnd/ranges/detail/iota_diff_t.hpp>
#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename It>
concept advanceable =
	detail::decrementable<It> &&
	bksge::totally_ordered<It> &&
	requires(It i, const It j, const detail::iota_diff_t<It> n)
	{
		{ i += n } -> bksge::same_as<It&>;
		{ i -= n } -> bksge::same_as<It&>;
		It(j + n);
		It(n + j);
		It(j - n);
		{ j - j } -> bksge::convertible_to<detail::iota_diff_t<It>>;
	};

template <typename It>
using is_advanceable = bksge::bool_constant<advanceable<It>>;

#else

template <typename It>
struct advanceable_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<detail::decrementable<I2>::value>,
		typename = bksge::enable_if_t<bksge::totally_ordered<I2>::value>,
		typename D = detail::iota_diff_t<I2>,
		typename T1 = decltype(std::declval<I2&>() += std::declval<D const>()),
		typename T2 = decltype(std::declval<I2&>() -= std::declval<D const>()),
		typename = decltype(I2(std::declval<I2 const>() + std::declval<D  const>())),
		typename = decltype(I2(std::declval<D  const>() + std::declval<I2 const>())),
		typename = decltype(I2(std::declval<I2 const>() - std::declval<D  const>())),
		typename T3 = decltype(std::declval<I2 const>() - std::declval<I2 const>())
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<T1, I2&>,
		bksge::same_as<T2, I2&>,
		bksge::convertible_to<T3, D>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<It>(0));
};

template <typename It>
using advanceable = typename advanceable_impl<It>::type;

template <typename It>
using is_advanceable = advanceable<It>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_ADVANCEABLE_HPP
