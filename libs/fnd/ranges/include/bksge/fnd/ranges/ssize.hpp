/**
 *	@file	ssize.hpp
 *
 *	@brief	ranges::ssize の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_SSIZE_HPP
#define BKSGE_FND_RANGES_SSIZE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

struct ssize_fn
{
private:
	template <typename T>
	struct result_type
	{
		using iter_type = decltype(ranges::begin(std::declval<T&&>()));
		using diff_type = bksge::iter_difference_t<iter_type>;
		using type = bksge::conditional_t<
			bksge::is_integral<diff_type>::value &&
			std::numeric_limits<diff_type>::digits < std::numeric_limits<std::ptrdiff_t>::digits,
			std::ptrdiff_t,
			diff_type
		>;
	};

	template <typename T>
	using result_type_t = typename result_type<T>::type;

public:
	template <
		typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = decltype(ranges::begin(std::declval<T&&>()))
		, typename = decltype(ranges::size(std::declval<T&&>()))
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires requires (T&& e)
	{
		ranges::begin(std::forward<T>(e));
		ranges::size(std::forward<T>(e));
	}
#endif
	BKSGE_CONSTEXPR result_type_t<T> operator()(T&& e) const
		BKSGE_NOEXCEPT_IF_EXPR(ranges::size(std::forward<T>(e)))
	{
		return static_cast<result_type_t<T>>(ranges::size(std::forward<T>(e)));
	}
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::ssize_fn ssize{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_SSIZE_HPP
