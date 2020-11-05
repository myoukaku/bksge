/**
 *	@file	drop_view.hpp
 *
 *	@brief	drop_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_DROP_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_DROP_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/range_size_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/detail/cached_position.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::view, V)>
class drop_view : public ranges::view_interface<drop_view<V>>
{
private:
	ranges::range_difference_t<V> m_count = 0;
	V m_base = {};

	static constexpr bool s_needs_cached_begin =
		!(ranges::is_random_access_range<V const>::value &&
		  ranges::is_sized_range<V const>::value);

	BKSGE_NO_UNIQUE_ADDRESS
	bksge::conditional_t<
		s_needs_cached_begin,
		ranges::detail::cached_position<V>,
		views::detail::Empty
	> m_cached_begin;

public:
	BKSGE_CONSTEXPR drop_view() = default;

	BKSGE_CXX14_CONSTEXPR
	drop_view(V base, ranges::range_difference_t<V> count)
		: m_count(count)
		, m_base(bksge::move(base))
	{
		BKSGE_ASSERT(count >= 0);
	}

	BKSGE_CONSTEXPR V base() const&
		BKSGE_REQUIRES(bksge::copy_constructible<V>)
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return bksge::move(m_base);
	}

private:
	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::false_type)
	-> ranges::iterator_t<V>
	{
		return ranges::next(ranges::begin(m_base), m_count, ranges::end(m_base));
	}

	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::true_type)
	-> ranges::iterator_t<V>
	{
		if (m_cached_begin.has_value())
		{
			return m_cached_begin.get(m_base);
		}

		auto it = begin_impl(bksge::false_type{});

		m_cached_begin.set(m_base, it);

		return it;
	}

public:
	template <typename V2 = V,
		typename = bksge::enable_if_t<
			!(ranges::detail::is_simple_view<V2>::value &&
			  ranges::is_random_access_range<V2 const>::value &&
			  ranges::is_sized_range<V2 const>::value)
		>
	>
	BKSGE_CXX14_CONSTEXPR auto begin()
	-> ranges::iterator_t<V2>
	{
		return begin_impl(bksge::bool_constant<s_needs_cached_begin>{});
	}

	template <typename V2 = V const,
		typename = bksge::enable_if_t<
			ranges::is_random_access_range<V2>::value &&
			ranges::is_sized_range<V2>::value
		>
	>
	BKSGE_CONSTEXPR auto begin() const
	-> ranges::iterator_t<V2>
	{
		return ranges::next(ranges::begin(m_base), m_count, ranges::end(m_base));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto end()
	-> ranges::sentinel_t<V2>
	{
		return ranges::end(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto end() const
	-> ranges::sentinel_t<V2>
	{
		return ranges::end(m_base);
	}

private:
	template <typename SizeType, typename CountType>
	static BKSGE_CONSTEXPR SizeType
	size_impl(SizeType s, CountType c)
	{
		return s < static_cast<SizeType>(c) ?
			0 :
			s - static_cast<SizeType>(c);
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto size()
	-> ranges::range_size_t<V2>
	{
		return size_impl(ranges::size(m_base), m_count);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V const)>
	BKSGE_CONSTEXPR auto size() const
	-> ranges::range_size_t<V2>
	{
		return size_impl(ranges::size(m_base), m_count);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
drop_view(Range&&, ranges::range_difference_t<Range>)
-> drop_view<views::all_t<Range>>;

#endif

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(T),
	drop_view<T>);

namespace views
{

namespace detail
{

struct drop_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename T>
	BKSGE_CONSTEXPR auto operator()(Range&& r, T&& n) const
	-> drop_view<views::all_t<Range>>
	{
		return {bksge::forward<Range>(r), bksge::forward<T>(n)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::drop_fn> drop{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_DROP_VIEW_HPP
