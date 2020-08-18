/**
 *	@file	subrange.hpp
 *
 *	@brief	ranges::subrange の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_SUBRANGE_HPP
#define BKSGE_FND_RANGES_VIEWS_SUBRANGE_HPP

#include <bksge/fnd/ranges/views/subrange_kind.hpp>
#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/detail/convertible_to_non_slicing.hpp>
#include <bksge/fnd/ranges/detail/not_same_as.hpp>
#include <bksge/fnd/ranges/detail/to_unsigned.hpp>
#include <bksge/fnd/ranges/detail/pair_like_convertible_from.hpp>
#include <bksge/fnd/ranges/detail/iterator_sentinel_pair.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/ranges/advance.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <
	bksge::input_or_output_iterator It,
	bksge::sentinel_for<It> Sent = It,
	ranges::subrange_kind Kind = bksge::sized_sentinel_for<Sent, It> ?
		ranges::subrange_kind::sized :
		ranges::subrange_kind::unsized
>
requires (Kind == ranges::subrange_kind::sized || !bksge::sized_sentinel_for<Sent, It>)
#else
template <
	typename It,
	typename Sent = It,
	ranges::subrange_kind Kind = bksge::sized_sentinel_for<Sent, It>::value ?
		ranges::subrange_kind::sized :
		ranges::subrange_kind::unsized,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::input_or_output_iterator<It>,
		bksge::sentinel_for<Sent, It>,
		bksge::bool_constant<
			Kind == ranges::subrange_kind::sized ||
			!bksge::sized_sentinel_for<Sent, It>::value
		>
	>::value>
>
#endif
class subrange : public ranges::view_interface<subrange<It, Sent, Kind>>
{
private:
	// XXX: gcc complains when using constexpr here
	static const bool StoreSize =
		Kind == ranges::subrange_kind::sized &&
		!bksge::is_sized_sentinel_for<Sent, It>::value;

	using size_type = bksge::make_unsigned_t<bksge::iter_difference_t<It>>;

	template <typename I, typename S, bool>
	struct subrange_base
	{
		I	m_begin = I();
		S	m_end   = S();

		subrange_base() = default;

		BKSGE_CXX14_CONSTEXPR subrange_base(I&& begin, S end)
			: m_begin(bksge::move(begin)), m_end(end) {}

		BKSGE_CXX14_CONSTEXPR subrange_base(I&& begin, S end, size_type)
			: m_begin(bksge::move(begin)), m_end(end) {}

		template <typename Rng>
		BKSGE_CXX14_CONSTEXPR subrange_base(Rng&& r)
			: subrange_base{ranges::begin(r), ranges::end(r)}
		{}

		BKSGE_CXX14_CONSTEXPR void move_forward(bksge::iter_difference_t<I> n)
		{
			ranges::advance(m_begin, n, m_end);
		}

		BKSGE_CXX14_CONSTEXPR void move_backward(bksge::iter_difference_t<I> n)
		{
			ranges::advance(m_begin, n);
		}

		BKSGE_CXX14_CONSTEXPR size_type get_size() const
		{
			return ranges::detail::to_unsigned(m_end - m_begin);
		}
	};

	template <typename I, typename S>
	struct subrange_base<I, S, true>
	{
		I	m_begin = I();
		S	m_end   = S();
		size_type m_size;

		subrange_base() = default;

		BKSGE_CXX14_CONSTEXPR subrange_base(It&& begin, S end, size_type n)
			: m_begin(bksge::move(begin)), m_end(end), m_size(n)
		{
			BKSGE_ASSERT(n == ranges::detail::to_unsigned(ranges::distance(begin, end)));
		}

		template <typename Rng>
		BKSGE_CXX14_CONSTEXPR subrange_base(Rng&& r)
			: subrange_base{ranges::begin(r), ranges::end(r), ranges::size(r)}
		{}

		BKSGE_CXX14_CONSTEXPR void move_forward(bksge::iter_difference_t<I> n)
		{
			auto d = n - ranges::advance(m_begin, n, m_end);
			m_size -= ranges::detail::to_unsigned(d);
		}

		BKSGE_CXX14_CONSTEXPR void move_backward(bksge::iter_difference_t<I> n)
		{
			ranges::advance(m_begin, n);
			m_size += ranges::detail::to_unsigned(-n);
		}

		BKSGE_CXX14_CONSTEXPR size_type get_size() const
		{
			return m_size;
		}
	};

	subrange_base<It, Sent, StoreSize>	m_value;

public:
	subrange() = default;

	template <BKSGE_REQUIRES_PARAM_2(ranges::detail::convertible_to_non_slicing, It, I2)>
	BKSGE_CXX14_CONSTEXPR
	subrange(I2 i, Sent s)
		BKSGE_REQUIRES(!StoreSize)
		: m_value{bksge::move(i), s}
	{}

	template <BKSGE_REQUIRES_PARAM_2(ranges::detail::convertible_to_non_slicing, It, I2)>
	BKSGE_CXX14_CONSTEXPR
	subrange(I2 i, Sent s, size_type n)
		BKSGE_REQUIRES(Kind == ranges::subrange_kind::sized)
		: m_value{bksge::move(i), s, n}
	{
		BKSGE_ASSERT(n == ranges::detail::to_unsigned(ranges::distance(i, s)));
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::detail::not_same_as<subrange> Rng>
	requires
		ranges::borrowed_range<Rng> &&
		ranges::detail::convertible_to_non_slicing<ranges::iterator_t<Rng>, It> &&
		bksge::convertible_to<ranges::sentinel_t<Rng>, Sent>
#else
	template <typename Rng,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::detail::not_same_as<Rng, subrange>,
			ranges::borrowed_range<Rng>,
			ranges::detail::convertible_to_non_slicing<ranges::iterator_t<Rng>, It>,
			bksge::convertible_to<ranges::sentinel_t<Rng>, Sent>,
			bksge::bool_constant<!StoreSize || ranges::sized_range<Rng>::value>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	subrange(Rng&& r)
		BKSGE_REQUIRES(!StoreSize || ranges::sized_range<Rng>)
		: m_value{r}
	{}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::borrowed_range Rng>
	requires
		ranges::detail::convertible_to_non_slicing<ranges::iterator_t<Rng>, It> &&
		bksge::convertible_to<ranges::sentinel_t<Rng>, Sent>
#else
	template <typename Rng,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::borrowed_range<Rng>,
			ranges::detail::convertible_to_non_slicing<ranges::iterator_t<Rng>, It>,
			bksge::convertible_to<ranges::sentinel_t<Rng>, Sent>,
			bksge::bool_constant<Kind == ranges::subrange_kind::sized>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	subrange(Rng&& r, size_type n)
		BKSGE_REQUIRES(Kind == ranges::subrange_kind::sized)
		: subrange{ranges::begin(r), ranges::end(r), n}
	{}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::detail::not_same_as<subrange> PairLike>
	requires ranges::detail::pair_like_convertible_from<PairLike, const It&, const Sent&>
#else
	template <typename PairLike,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::detail::not_same_as<PairLike, subrange>,
			ranges::detail::pair_like_convertible_from<PairLike, const It&, const Sent&>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator PairLike() const
	{
		return PairLike(m_value.m_begin, m_value.m_end);
	}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <BKSGE_REQUIRES_PARAM_D(bksge::copyable, I, It)>
#endif
	BKSGE_CXX14_CONSTEXPR It begin() const
		BKSGE_REQUIRES(bksge::copyable<It>)
	{
		return m_value.m_begin;
	}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <BKSGE_REQUIRES_PARAM_D(!bksge::copyable, I, It)>
#endif
	BKSGE_NODISCARD
	BKSGE_CXX14_CONSTEXPR It begin()
		BKSGE_REQUIRES(!bksge::copyable<It>)
	{
		return bksge::move(m_value.m_begin);
	}

	BKSGE_CXX14_CONSTEXPR Sent end() const
	{
		return m_value.m_end;
	}

	BKSGE_CXX14_CONSTEXPR bool empty() const
	{
		return m_value.m_begin == m_value.m_end;
	}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::subrange_kind K = Kind,
		typename = bksge::enable_if_t<K == ranges::subrange_kind::sized>
	>
#endif
	BKSGE_CXX14_CONSTEXPR size_type
	size() const
		BKSGE_REQUIRES(Kind == ranges::subrange_kind::sized)
	{
		return m_value.get_size();
	}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <BKSGE_REQUIRES_PARAM_D(bksge::forward_iterator, I, It)>
#endif
	BKSGE_NODISCARD
	BKSGE_CXX14_CONSTEXPR subrange
	next(bksge::iter_difference_t<It> n = 1) const&
		BKSGE_REQUIRES(bksge::forward_iterator<It>)
	{
		auto tmp = *this;
		tmp.advance(n);
		return tmp;
	}

	BKSGE_NODISCARD
	BKSGE_CXX14_CONSTEXPR subrange
	next(bksge::iter_difference_t<It> n = 1) &&
	{
		advance(n);
		return bksge::move(*this);
	}

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <BKSGE_REQUIRES_PARAM_D(bksge::bidirectional_iterator, I, It)>
#endif
	BKSGE_NODISCARD
	BKSGE_CXX14_CONSTEXPR subrange
	prev(bksge::iter_difference_t<It> n = 1) const
		BKSGE_REQUIRES(bksge::bidirectional_iterator<It>)
	{
		auto tmp = *this;
		tmp.advance(-n);
		return tmp;
	}

private:
	BKSGE_CXX14_CONSTEXPR subrange&
	advance_impl(bksge::iter_difference_t<It> n, bksge::true_type)
	{
		if (n < 0)
		{
			m_value.move_backward(n);
		}
		else
		{
			m_value.move_forward(n);
		}
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR subrange&
	advance_impl(bksge::iter_difference_t<It> n, bksge::false_type)
	{
		BKSGE_ASSERT(n >= 0);
		m_value.move_forward(n);
		return *this;
	}

public:
	BKSGE_CXX14_CONSTEXPR subrange&
	advance(bksge::iter_difference_t<It> n)
	{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		return advance_impl(n, bksge::bool_constant<bksge::bidirectional_iterator<It>>{});
#else
		return advance_impl(n, bksge::bidirectional_iterator<It>{});
#endif
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

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
subrange(It, Sent)
	-> subrange<It, Sent>;

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
subrange(It, Sent, bksge::make_unsigned_t<bksge::iter_difference_t<It>>)
	-> subrange<It, Sent, ranges::subrange_kind::sized>;

#if 0
// https://cplusplus.github.io/LWG/issue3281
// pair-like types を引数に取るコンストラクタは削除されたので、
// この deduction guide は要らないのでは？

template <ranges::detail::iterator_sentinel_pair Pair>
subrange(Pair)
	->subrange<bksge::tuple_element_t<0, Pair>, bksge::tuple_element_t<1, Pair>>;

template <ranges::detail::iterator_sentinel_pair Pair>
subrange(Pair, bksge::make_unsigned_t<bksge::iter_difference_t<bksge::tuple_element_t<0, Pair>>>)
	->subrange<bksge::tuple_element_t<0, Pair>, bksge::tuple_element_t<1, Pair>, ranges::subrange_kind::sized>;

#endif

template <BKSGE_REQUIRES_PARAM(ranges::borrowed_range, Rng)>
subrange(Rng&&)
	-> subrange<ranges::iterator_t<Rng>, ranges::sentinel_t<Rng>,
		((ranges::is_sized_range<Rng>::value ||
		 bksge::is_sized_sentinel_for<ranges::sentinel_t<Rng>, ranges::iterator_t<Rng>>::value) ?
			ranges::subrange_kind::sized :
			ranges::subrange_kind::unsized)
	>;

template <BKSGE_REQUIRES_PARAM(ranges::borrowed_range, Rng)>
subrange(Rng&&, bksge::make_unsigned_t<ranges::range_difference_t<Rng>>)
	->subrange<ranges::iterator_t<Rng>, ranges::sentinel_t<Rng>, ranges::subrange_kind::sized>;

#endif	// #if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

namespace detail
{

template <std::size_t N>
struct subrange_get;

template <>
struct subrange_get<0>
{
	template <typename R>
	BKSGE_CXX14_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.begin())
	{
		return r.begin();
	}
};
template <>
struct subrange_get<1>
{
	template <typename R>
	BKSGE_CXX14_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.end())
	{
		return r.end();
	}
};

}	// namespace detail

template <std::size_t Num, typename It, typename Sent, ranges::subrange_kind Kind>
	BKSGE_REQUIRES(Num < 2)
BKSGE_CXX14_CONSTEXPR auto get(subrange<It, Sent, Kind> const& r)
->decltype(detail::subrange_get<Num>()(r))
{
	return detail::subrange_get<Num>()(r);
}

template <std::size_t Num, typename It, typename Sent, ranges::subrange_kind Kind>
	BKSGE_REQUIRES(Num < 2)
BKSGE_CXX14_CONSTEXPR auto get(subrange<It, Sent, Kind>&& r)
->decltype(detail::subrange_get<Num>()(bksge::move(r)))
{
	return detail::subrange_get<Num>()(bksge::move(r));
}

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::input_or_output_iterator It,
	bksge::sentinel_for<It> Sent,
#else
	typename It,
	typename Sent,
#endif
	ranges::subrange_kind Kind
>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, subrange<It, Sent, Kind>);

}	// namespace ranges

using ranges::get;

}	// namespace bksge

namespace std
{

template <typename Iter, typename Sent, bksge::ranges::subrange_kind Kind>
struct tuple_size<bksge::ranges::subrange<Iter, Sent, Kind>>
	: public bksge::integral_constant<std::size_t, 2>
{
};

template <typename Iter, typename Sent, bksge::ranges::subrange_kind Kind>
struct tuple_element<0, bksge::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Iter;
};

template <typename Iter, typename Sent, bksge::ranges::subrange_kind Kind>
struct tuple_element<1, bksge::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Sent;
};

template <typename Iter, typename Sent, bksge::ranges::subrange_kind Kind>
struct tuple_element<0, const bksge::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Iter;
};

template <typename Iter, typename Sent, bksge::ranges::subrange_kind Kind>
struct tuple_element<1, const bksge::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Sent;
};

}	// namespace std

#endif // BKSGE_FND_RANGES_VIEWS_SUBRANGE_HPP
