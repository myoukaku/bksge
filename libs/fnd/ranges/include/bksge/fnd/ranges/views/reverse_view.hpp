/**
 *	@file	reverse_view.hpp
 *
 *	@brief	reverse_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_REVERSE_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_REVERSE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/views/subrange_kind.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor_closure.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_present_t.hpp>
#include <bksge/fnd/ranges/detail/cached_position.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_size_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::view V>
requires ranges::bidirectional_range<V>
#else
template <typename V,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::view<V>,
		ranges::bidirectional_range<V>
	>::value>
>
#endif
class reverse_view : public ranges::view_interface<reverse_view<V>>
{
private:
	using s_needs_cached_begin = bksge::conjunction<
		bksge::negation<ranges::is_common_range<V>>,
		bksge::negation<ranges::is_random_access_range<V>>>;

	BKSGE_NO_UNIQUE_ADDRESS
	ranges::detail::maybe_present_t<
		s_needs_cached_begin::value,
		ranges::detail::cached_position<V>
	> m_cached_begin;

	V m_base = {};

public:
	BKSGE_CONSTEXPR reverse_view() = default;

	BKSGE_CXX14_CONSTEXPR explicit
	reverse_view(V r)
		: m_base(std::move(r))
	{}

	template <BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, V2, V)>
	BKSGE_CONSTEXPR V base() const&
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return std::move(m_base);
	}

private:
	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::false_type)
	-> bksge::reverse_iterator<ranges::iterator_t<V>>
	{
		auto it = ranges::next(ranges::begin(m_base), ranges::end(m_base));
		return bksge::make_reverse_iterator(std::move(it));
	}

	BKSGE_CXX14_CONSTEXPR auto begin_impl(bksge::true_type)
	-> bksge::reverse_iterator<ranges::iterator_t<V>>
	{
		if (m_cached_begin.has_value())
		{
			return bksge::make_reverse_iterator(m_cached_begin.get(m_base));
		}

		auto it = ranges::next(ranges::begin(m_base), ranges::end(m_base));
		m_cached_begin.set(m_base, it);
		return bksge::make_reverse_iterator(std::move(it));
	}

public:
	BKSGE_CXX14_CONSTEXPR auto begin()
	-> bksge::reverse_iterator<ranges::iterator_t<V>>
	{
		return begin_impl(s_needs_cached_begin{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto begin()
	-> bksge::reverse_iterator<ranges::iterator_t<V2>>
	{
		return bksge::make_reverse_iterator(ranges::end(m_base));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V const)>
	BKSGE_CONSTEXPR auto begin() const
	-> bksge::reverse_iterator<ranges::iterator_t<V2>>
	{
		return bksge::make_reverse_iterator(ranges::end(m_base));
	}

	BKSGE_CXX14_CONSTEXPR auto end()
	-> bksge::reverse_iterator<ranges::iterator_t<V>>
	{
		return bksge::make_reverse_iterator(ranges::begin(m_base));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::common_range, V2, V const)>
	BKSGE_CONSTEXPR auto end() const
	-> bksge::reverse_iterator<ranges::iterator_t<V2>>
	{
		return bksge::make_reverse_iterator(ranges::begin(m_base));
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
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
reverse_view(Range&&) -> reverse_view<views::all_t<Range>>;

#endif

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(T),
	reverse_view<T>);

namespace views
{

namespace detail
{

template <typename>
struct is_reverse_view
	: public bksge::false_type {};

template <typename V>
struct is_reverse_view<ranges::reverse_view<V>>
	: public bksge::true_type {};

template <typename>
struct is_reversible_subrange
	: public bksge::false_type {};

template <typename Iter, ranges::subrange_kind Kind>
struct is_reversible_subrange<
	ranges::subrange<
		bksge::reverse_iterator<Iter>,
		bksge::reverse_iterator<Iter>,
		Kind>>
	: public bksge::true_type {};

struct reverse_fn
{
private:
	template <
		typename Range,
		typename T = bksge::remove_cvref_t<Range>,
		typename = bksge::enable_if_t<views::detail::is_reverse_view<T>::value>
	>
	BKSGE_CONSTEXPR auto impl(Range&& r, bksge::detail::overload_priority<3>) const
	->decltype(bksge::forward<Range>(r).base())
	{
		return bksge::forward<Range>(r).base();
	}

	template <
		typename Range,
		typename T = bksge::remove_cvref_t<Range>,
		typename = bksge::enable_if_t<views::detail::is_reversible_subrange<T>::value>,
		typename = bksge::enable_if_t<ranges::is_sized_range<T>::value>,
		typename Iter = decltype(ranges::begin(std::declval<Range>()).base())
	>
	BKSGE_CONSTEXPR auto impl(Range&& r, bksge::detail::overload_priority<2>) const
	-> ranges::subrange<Iter, Iter, ranges::subrange_kind::sized>
	{
		return { r.end().base(), r.begin().base(), r.size() };
	}

	template <
		typename Range,
		typename T = bksge::remove_cvref_t<Range>,
		typename = bksge::enable_if_t<views::detail::is_reversible_subrange<T>::value>,
		typename Iter = decltype(ranges::begin(std::declval<Range>()).base())
	>
	BKSGE_CONSTEXPR auto impl(Range&& r, bksge::detail::overload_priority<1>) const
	-> ranges::subrange<Iter, Iter, ranges::subrange_kind::unsized>
	{
		return { r.end().base(), r.begin().base() };
	}

	template <typename Range>
	BKSGE_CONSTEXPR auto impl(Range&& r, bksge::detail::overload_priority<0>) const
	-> ranges::reverse_view<views::all_t<Range>>
	{
		return ranges::reverse_view<views::all_t<Range>>{bksge::forward<Range>(r)};
	}

public:
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CONSTEXPR auto operator()(Range&& r) const
	->decltype(impl(bksge::forward<Range>(r), bksge::detail::overload_priority<3>{}))
	{
		return impl(bksge::forward<Range>(r), bksge::detail::overload_priority<3>{});
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::reverse_fn> reverse{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_REVERSE_VIEW_HPP
