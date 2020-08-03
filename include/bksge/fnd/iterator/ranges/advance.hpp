/**
 *	@file	advance.hpp
 *
 *	@brief	ranges::advance 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_ADVANCE_HPP
#define BKSGE_FND_ITERATOR_RANGES_ADVANCE_HPP

#include <iterator>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)

namespace bksge
{
namespace ranges
{

using std::ranges::advance;

}	// namespace ranges
}	// namespace bksge

#else

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <BKSGE_REQUIRE(bksge::random_access_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_1(bksge::detail::overload_priority<2>, It& it, bksge::iter_difference_t<It> n)
{
	it += n;
}

template <BKSGE_REQUIRE(bksge::bidirectional_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_1(bksge::detail::overload_priority<1>, It& it, bksge::iter_difference_t<It> n)
{
	if (n > 0)
	{
		do
		{
			++it;
		} while (--n);
	}
	else if (n < 0)
	{
		do
		{
			--it;
		} while (++n);
	}
}

template <typename It>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_1(bksge::detail::overload_priority<0>, It& it, bksge::iter_difference_t<It> n)
{
#ifdef __cpp_lib_is_constant_evaluated
	if (std::is_constant_evaluated() && n < 0)
	{
		throw "attempt to decrement a non-bidirectional iterator";
	}
#endif
	BKSGE_ASSERT(n >= 0);
	while (n-- > 0)
	{
		++it;
	}
}

}	// namespace detail

template <BKSGE_REQUIRE(bksge::input_or_output_iterator, It)>
inline BKSGE_CXX14_CONSTEXPR void
advance(It& it, bksge::iter_difference_t<It> n)
{
	ranges::detail::advance_impl_1(bksge::detail::overload_priority<2>{}, it, n);
}

namespace detail
{

template <
	typename It, typename Sent
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, typename = bksge::enable_if_t<bksge::assignable_from<It&, Sent>::value>
#endif
>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires bksge::assignable_from<It&, Sent>
#endif
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_2(bksge::detail::overload_priority<2>, It& it, Sent bound)
{
	it = bksge::move(bound);
}

template <
	typename It,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = bksge::enable_if_t<bksge::sized_sentinel_for<Sent, It>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_2(bksge::detail::overload_priority<1>, It& it, Sent bound)
{
	ranges::advance(it, bound - it);
}

template <typename It, typename Sent>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl_2(bksge::detail::overload_priority<0>, It& it, Sent bound)
{
	while (it != bound)
	{
		++it;
	}
}

}	// namespace detail

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::input_or_output_iterator It, bksge::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::input_or_output_iterator<It>,
		bksge::sentinel_for<Sent, It>
	>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR void
advance(It& it, Sent bound)
{
	ranges::detail::advance_impl_2(bksge::detail::overload_priority<2>{}, it, bound);
}

namespace detail
{

template <
	typename It, typename Difference,
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = bksge::enable_if_t<bksge::sized_sentinel_for<Sent, It>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR Difference
advance_impl_3(bksge::detail::overload_priority<1>, It& it, Difference n, Sent bound)
{
	const auto diff = bound - it;
#ifdef __cpp_lib_is_constant_evaluated
	if (std::is_constant_evaluated() && !(n == 0 || diff == 0 || ((n < 0) == (diff < 0))))
	{
		throw "inconsistent directions for distance and bound";
	}
#endif
	// n and bound must not lead in opposite directions:
	BKSGE_ASSERT(n == 0 || diff == 0 || ((n < 0) == (diff < 0)));
	const auto absdiff = diff < 0 ? -diff : diff;
	const auto absn = n < 0 ? -n : n;;
	if (absn >= absdiff)
	{
		ranges::advance(it, bound);
		return n - diff;
	}
	else
	{
		ranges::advance(it, n);
		return 0;
	}
}

template <
	typename It, typename Difference, typename Sent
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, typename = bksge::enable_if_t<
		bksge::bidirectional_iterator<It>::value &&
		bksge::same_as<It, Sent>::value
	>
#endif
>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires bksge::bidirectional_iterator<It> && bksge::same_as<It, Sent>
#endif
inline BKSGE_CXX14_CONSTEXPR Difference
advance_impl_4(bksge::detail::overload_priority<1>, It& it, Difference n, Sent bound)
{
	bksge::iter_difference_t<It> m = 0;
	do
	{
		--it;
		--m;
	} while (m != n && it != bound);

	return n - m;
}

template <typename It, typename Difference, typename Sent>
inline BKSGE_CXX14_CONSTEXPR Difference
advance_impl_4(bksge::detail::overload_priority<0>, It& /*it*/, Difference n, Sent /*bound*/)
{
#ifdef __cpp_lib_is_constant_evaluated
	if (std::is_constant_evaluated() && n < 0)
	{
		throw "attempt to decrement a non-bidirectional iterator";
	}
#endif
	BKSGE_ASSERT(n >= 0);
	return n;
}

template <typename It, typename Difference, typename Sent>
inline BKSGE_CXX14_CONSTEXPR Difference
advance_impl_3(bksge::detail::overload_priority<0>, It& it, Difference n, Sent bound)
{
	if (it == bound || n == 0)
	{
		return bksge::iter_difference_t<It>(0);
	}
	else if (n > 0)
	{
		bksge::iter_difference_t<It> m = 0;
		do
		{
			++it;
			++m;
		} while (m != n && it != bound);

		return n - m;
	}
	else
	{
		return advance_impl_4(
			bksge::detail::overload_priority<1>{}, it, n, bound);
	}
}

}	// namespace detail

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::input_or_output_iterator It, bksge::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::input_or_output_iterator<It>,
		bksge::sentinel_for<Sent, It>
	>::value>
#endif
>
inline BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<It>
advance(It& it, bksge::iter_difference_t<It> n, Sent bound)
{
	return ranges::detail::advance_impl_3(
		bksge::detail::overload_priority<1>{}, it, n, bound);
}

}	// namespace ranges

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_RANGES_ADVANCE_HPP
