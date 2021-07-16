/**
 *	@file	common_view.hpp
 *
 *	@brief	common_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_COMMON_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_COMMON_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor_closure.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/common_iterator.hpp>
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
requires (!ranges::common_range<V>) && bksge::copyable<ranges::iterator_t<V>>
#else
template <typename V,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::view<V>,
		bksge::negation<ranges::common_range<V>>,
		bksge::copyable<ranges::iterator_t<V>>
	>::value>
>
#endif
class common_view : public ranges::view_interface<common_view<V>>
{
private:
	V m_base = {};

public:
	BKSGE_CONSTEXPR common_view() = default;

	BKSGE_CXX14_CONSTEXPR explicit
	common_view(V r)
		: m_base(std::move(r))
	{}

	/* XXX: LWG 3280 didn't remove this constructor, but I think it should?
	template <ranges::viewable_range Range>
	requires (!ranges::common_range<Range>) &&
		constructible_from<V, views::all_t<Range>>
	constexpr explicit
	common_view(Range&& r)
		: m_base(views::all(bksge::forward<Range>(r)))
	{}
	*/

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
	template <
		typename V2,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_random_access_range<V2>,
			ranges::is_sized_range<V2>
		>::value>,
		typename ThisType
	>
	static BKSGE_CONSTEXPR auto
	begin_impl(ThisType* this_, bksge::detail::overload_priority<1>)
	->decltype(ranges::begin(this_->m_base))
	{
		return ranges::begin(this_->m_base);
	}

	template <
		typename V2,
		typename I = ranges::iterator_t<V2>,
		typename S = ranges::sentinel_t<V2>,
		typename ThisType
	>
	static BKSGE_CONSTEXPR bksge::common_iterator<I, S>
	begin_impl(ThisType* this_, bksge::detail::overload_priority<0>)
	{
		return { ranges::begin(this_->m_base) };
	}

public:
	template <typename V2 = V>
	BKSGE_CXX14_CONSTEXPR auto begin()
	->decltype(begin_impl<V2>(this, bksge::detail::overload_priority<1>{}))
	{
		return begin_impl<V2>(this, bksge::detail::overload_priority<1>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto begin() const
	->decltype(begin_impl<V2>(this, bksge::detail::overload_priority<1>{}))
	{
		return begin_impl<V2>(this, bksge::detail::overload_priority<1>{});
	}

private:
	template <
		typename V2,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_random_access_range<V2>,
			ranges::is_sized_range<V2>
		>::value>,
		typename ThisType
	>
	static BKSGE_CONSTEXPR auto
	end_impl(ThisType* this_, bksge::detail::overload_priority<1>)
	->decltype(ranges::begin(this_->m_base) + ranges::size(this_->m_base))
	{
		return ranges::begin(this_->m_base) + ranges::size(this_->m_base);
	}

	template <
		typename V2,
		typename I = ranges::iterator_t<V2>,
		typename S = ranges::sentinel_t<V2>,
		typename ThisType
	>
	static BKSGE_CONSTEXPR bksge::common_iterator<I, S>
	end_impl(ThisType* this_, bksge::detail::overload_priority<0>)
	{
		return { ranges::end(this_->m_base) };
	}

public:
	template <typename V2 = V>
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl<V2>(this, bksge::detail::overload_priority<1>{}))
	{
		return end_impl<V2>(this, bksge::detail::overload_priority<1>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl<V2>(this, bksge::detail::overload_priority<1>{}))
	{
		return end_impl<V2>(this, bksge::detail::overload_priority<1>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto size()
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::size(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V const)>
	BKSGE_CONSTEXPR auto size() const
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::size(m_base);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
common_view(Range&&) -> common_view<views::all_t<Range>>;

#endif

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(T),
	common_view<T>);

namespace views
{

namespace detail
{

struct common_fn
{
private:
	template <BKSGE_REQUIRES_PARAM(ranges::common_range, Range)>
	static BKSGE_CONSTEXPR views::all_t<Range>
	impl(Range&& r, bksge::detail::overload_priority<1>)
		BKSGE_REQUIRES(requires { views::all(bksge::forward<Range>(r)); })
	{
		return views::all(bksge::forward<Range>(r));
	}

	template <typename Range>
	static BKSGE_CONSTEXPR common_view<views::all_t<Range>>
	impl(Range&& r, bksge::detail::overload_priority<0>)
	{
		return common_view<views::all_t<Range>>{bksge::forward<Range>(r)};
	}

public:
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range)>
	BKSGE_CONSTEXPR auto operator()(Range&& r) const
	->decltype(impl(bksge::forward<Range>(r), bksge::detail::overload_priority<1>{}))
	{
		return impl(bksge::forward<Range>(r), bksge::detail::overload_priority<1>{});
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor_closure<views::detail::common_fn> common{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_COMMON_VIEW_HPP
