/**
 *	@file	elements_view.hpp
 *
 *	@brief	elements_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_ELEMENTS_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_ELEMENTS_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor_closure.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/range_size_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, bksge::size_t N>
concept has_tuple_element =
	requires(T t)
	{
		typename bksge::tuple_size<T>::type;
		requires N < bksge::tuple_size<T>::value;
		typename bksge::tuple_element_t<N, T>;
		{ get<N>(t) } -> bksge::convertible_to<bksge::tuple_element_t<N, T> const&>;
	};

#else

template <typename T, bksge::size_t N>
struct has_tuple_element_impl
{
private:
	template <typename T2, bksge::size_t N2,
		typename = typename bksge::tuple_size<T2>::type,
		typename = typename bksge::tuple_element_t<N2, T2>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::bool_constant<(N2 < bksge::tuple_size<T2>::value)>,
		bksge::convertible_to<
			decltype(get<N2>(bksge::declval<T2&>())),
			bksge::tuple_element_t<N2, T2> const&
		>
	>;

	template <typename T2, bksge::size_t N2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, N>(0));
};

template <typename T, bksge::size_t N>
using has_tuple_element = typename has_tuple_element_impl<T, N>::type;

#endif

}	// namespace detail

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::input_range V, bksge::size_t N>
requires ranges::view<V> &&
	ranges::detail::has_tuple_element<ranges::range_value_t<V>, N> &&
	ranges::detail::has_tuple_element<bksge::remove_reference_t<ranges::range_reference_t<V>>, N>
#else
template <typename V, bksge::size_t N,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::input_range<V>,
		ranges::view<V>,
		ranges::detail::has_tuple_element<ranges::range_value_t<V>, N>,
		ranges::detail::has_tuple_element<bksge::remove_reference_t<ranges::range_reference_t<V>>, N>
	>::value>
>
#endif
class elements_view : public ranges::view_interface<elements_view<V, N>>
{
private:
	template <bool Const>
	struct Sentinel;

	template <bool Const>
	struct Iterator;

public:
	BKSGE_CONSTEXPR elements_view() = default;

	BKSGE_CONSTEXPR explicit
	elements_view(V base)
		: m_base(bksge::move(base))
	{}

	template <BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, V2, V)>
	BKSGE_CONSTEXPR V base() const&
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return bksge::move(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR Iterator<false> begin()
	{
		return Iterator<false>(ranges::begin(m_base));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR Iterator<true> begin() const
	{
		return Iterator<true>(ranges::begin(m_base));
	}

private:
	BKSGE_CXX14_CONSTEXPR Sentinel<false> end_impl(bksge::false_type)
	{
		return Sentinel<false>{ranges::end(m_base)};
	}

	BKSGE_CXX14_CONSTEXPR Iterator<false> end_impl(bksge::true_type)
	{
		return Iterator<false>{ranges::end(m_base)};
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl(ranges::is_common_range<V2>{}))
	{
		return end_impl(ranges::is_common_range<V2>{});
	}

private:
	BKSGE_CONSTEXPR Sentinel<true> end_impl(bksge::false_type) const
	{
		return Sentinel<true>{ranges::end(m_base)};
	}

	BKSGE_CONSTEXPR Iterator<true> end_impl(bksge::true_type) const
	{
		return Iterator<true>{ranges::end(m_base)};
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl(ranges::is_common_range<V2>{}))
	{
		return end_impl(ranges::is_common_range<V2>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto size()
	-> ranges::range_size_t<V2>
	{
		return ranges::size(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V const)>
	BKSGE_CONSTEXPR auto size() const
	-> ranges::range_size_t<V2>
	{
		return ranges::size(m_base);
	}

private:
	template <bool Const>
	struct Iterator
	{
		using Base = ranges::detail::maybe_const_t<Const, V>;

		ranges::iterator_t<Base> m_current = {};

		friend Iterator<!Const>;

	public:
		using iterator_category = typename bksge::iterator_traits<ranges::iterator_t<Base>>::iterator_category;
		using value_type = bksge::remove_cvref_t<bksge::tuple_element_t<N, ranges::range_value_t<Base>>>;
		using difference_type = ranges::range_difference_t<Base>;

		BKSGE_CONSTEXPR Iterator() = default;

		BKSGE_CONSTEXPR explicit
		Iterator(ranges::iterator_t<Base> current)
			: m_current(bksge::move(current))
		{}

		template <bool Const2 = Const,
			typename = bksge::enable_if_t<
				Const2 &&
				bksge::is_convertible_to<
					ranges::iterator_t<V>,
					ranges::iterator_t<Base>
				>::value>>
		BKSGE_CONSTEXPR
		Iterator(Iterator<!Const> i)
			: m_current(bksge::move(i.m_current))
		{}

		template <BKSGE_REQUIRES_PARAM_D(bksge::copyable, I, ranges::iterator_t<Base>)>
		BKSGE_CONSTEXPR ranges::iterator_t<Base> base() const&
		{
			return m_current;
		}

		BKSGE_CXX14_CONSTEXPR ranges::iterator_t<Base> base() &&
		{
			return bksge::move(m_current);
		}

		BKSGE_CONSTEXPR auto operator*() const
		->decltype((get<N>(*m_current)))
		{
			return get<N>(*m_current);
		}

		BKSGE_CXX14_CONSTEXPR Iterator& operator++()
		{
			++m_current;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::not_forward_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR void operator++(int)
		{
			++m_current;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator operator++(int)
		{
			auto tmp = *this;
			++m_current;
			return tmp;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator--()
		{
			--m_current;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator operator--(int)
		{
			auto tmp = *this;
			--m_current;
			return tmp;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator+=(difference_type n)
		{
			m_current += n;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CXX14_CONSTEXPR Iterator& operator-=(difference_type n)
		{
			m_current -= n;
			return *this;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		BKSGE_CONSTEXPR auto operator[](difference_type n) const
		->decltype((get<N>(*m_current)))
		{
			return get<N>(*(m_current + n));
		}

		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, I, ranges::iterator_t<Base>)>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_current == rhs.m_current;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <BKSGE_REQUIRES_PARAM_D(bksge::equality_comparable, I, ranges::iterator_t<Base>)>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator<(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_current < rhs.m_current;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator>(Iterator const& lhs, Iterator const& rhs)
		{
			return rhs < lhs;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator<=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(rhs < lhs);
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR bool
		operator>=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs < rhs);
		}

#if 0//def __cpp_lib_three_way_comparison
		friend BKSGE_CONSTEXPR auto
		operator<=>(Iterator const& lhs, Iterator const& rhs)
			requires ranges::random_access_range<Base> &&
				three_way_comparable<ranges::iterator_t<Base>>
		{
			return lhs.m_current <=> rhs.m_current;
		}
#endif

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(Iterator const& lhs, difference_type rhs)
		{
			return Iterator{lhs} += rhs;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator+(difference_type lhs, Iterator const& rhs)
		{
			return rhs + lhs;
		}

		template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, B2, Base)>
		friend BKSGE_CONSTEXPR Iterator
		operator-(Iterator const& lhs, difference_type rhs)
		{
			return Iterator{lhs} -= rhs;
		}

		template <typename B2 = Base,
			typename = bksge::enable_if_t<
				bksge::is_sized_sentinel_for<
					ranges::iterator_t<B2>,
					ranges::iterator_t<B2>
				>::value>>
		friend BKSGE_CONSTEXPR difference_type
		operator-(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_current - rhs.m_current;
		}

		friend Sentinel<Const>;
	};

	template <bool Const>
	struct Sentinel
	{
	private:
		BKSGE_CONSTEXPR bool
		equal(Iterator<Const> const& lhs) const
		{
			return lhs.m_current == m_end;
		}

		using Base = ranges::detail::maybe_const_t<Const, V>;
		ranges::sentinel_t<Base> m_end = {};

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(ranges::sentinel_t<Base> end)
			: m_end(bksge::move(end))
		{}

		template <bool Const2 = Const,
			typename = bksge::enable_if_t<
				Const2 &&
				bksge::is_convertible_to<
					ranges::sentinel_t<V>,
					ranges::sentinel_t<Base>
				>::value>>
		BKSGE_CONSTEXPR
		Sentinel(Sentinel<!Const> other)
			: m_end(bksge::move(other.m_end))
		{}

		BKSGE_CONSTEXPR ranges::sentinel_t<Base> base() const
		{
			return m_end;
		}

	private:
		template <bool Const2,
			typename Base2 = ranges::detail::maybe_const_t<Const2, V>>
		using IsSentinel =
			bksge::is_sentinel_for<
				ranges::sentinel_t<Base>,
				ranges::iterator_t<Base2>
			>;

	public:
		template <bool Const2, typename = bksge::enable_if_t<IsSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return rhs.equal(lhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool Const2, typename = bksge::enable_if_t<IsSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return rhs == lhs;
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

	private:
		template <bool Const2,
			typename Base2 = ranges::detail::maybe_const_t<Const2, V>>
		using IsSizedSentinel =
			bksge::is_sized_sentinel_for<
				ranges::sentinel_t<Base>,
				ranges::iterator_t<Base2>
			>;

	public:
		template <bool Const2, typename = bksge::enable_if_t<IsSizedSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR ranges::range_difference_t<Base>
		operator-(Iterator<Const2> const& lhs, Sentinel const& rhs)
		{
			return lhs.m_current - rhs.m_end;
		}

		template <bool Const2, typename = bksge::enable_if_t<IsSizedSentinel<Const2>::value>>
		friend BKSGE_CONSTEXPR ranges::range_difference_t<Base>
		operator-(Sentinel const& lhs, Iterator<Const2> const& rhs)
		{
			return lhs.m_end - rhs.m_current;
		}

		friend Sentinel<!Const>;
	};

	V m_base = {};
};

template <typename T, bksge::size_t N>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(T),
	elements_view<T, N>);

template <typename Range>
using keys_view   = elements_view<views::all_t<Range>, 0>;

template <typename Range>
using values_view = elements_view<views::all_t<Range>, 1>;

namespace views
{

namespace detail
{

template <bksge::size_t N>
struct elements_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CONSTEXPR auto operator()(Range&& r) const
	-> elements_view<views::all_t<Range>, N>
	{
		return elements_view<views::all_t<Range>, N>{ bksge::forward<Range>(r) };
	}
};

}	// namespace detail

template <bksge::size_t N>
using elements_t =
	views::detail::range_adaptor_closure<views::detail::elements_fn<N>>;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <bksge::size_t N>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR elements_t<N> elements{};

#endif

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::elements_fn<0>> keys{};
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::elements_fn<1>> values{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_ELEMENTS_VIEW_HPP
