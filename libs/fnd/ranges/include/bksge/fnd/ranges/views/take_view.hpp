/**
 *	@file	take_view.hpp
 *
 *	@brief	ranges::take_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_TAKE_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_TAKE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/min.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/counted_iterator.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::view, V)>
class take_view : public ranges::view_interface<take_view<V>>
{
private:
	template <bool Const>
	using CI = bksge::counted_iterator<
		ranges::iterator_t<ranges::detail::maybe_const_t<Const, V>>>;

	template <bool Const>
	struct Sentinel
	{
	private:
		using Base = ranges::detail::maybe_const_t<Const, V>;

		ranges::sentinel_t<Base> m_end = {};

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(ranges::sentinel_t<Base> end)
			: m_end(end)
		{}

		template <bool C2 = Const,
			typename = bksge::enable_if_t<
				C2 &&
				bksge::is_convertible_to<
					ranges::sentinel_t<V>,
					ranges::sentinel_t<Base>>::value>>
		BKSGE_CXX14_CONSTEXPR
		Sentinel(Sentinel<!Const> s)
			: m_end(std::move(s.m_end))
		{}

		BKSGE_CONSTEXPR ranges::sentinel_t<Base> base() const
		{
			return m_end;
		}

		friend BKSGE_CONSTEXPR bool
		operator==(CI<Const> const& lhs, Sentinel const& rhs)
		{
			return lhs.count() == 0 || lhs.base() == rhs.m_end;
		}

		template <bool OtherConst = !Const,
			typename Base2 = ranges::detail::maybe_const_t<OtherConst, V>,
			typename = bksge::enable_if_t<
				bksge::is_sentinel_for<
					ranges::sentinel_t<Base>,
					ranges::iterator_t<Base2>
				>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(CI<OtherConst> const& lhs, Sentinel const& rhs)
		{
			return lhs.count() == 0 || lhs.base() == rhs.m_end;
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(CI<Const> const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, CI<Const> const& rhs)
		{
			return rhs == lhs;
		}

		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, CI<Const> const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		friend Sentinel<!Const>;
	};

	using Difference = ranges::range_difference_t<V>;

	Difference m_count = 0;
	V          m_base  = {};

public:
	BKSGE_CONSTEXPR take_view() = default;

	BKSGE_CXX14_CONSTEXPR
	take_view(V base, ranges::range_difference_t<V> count)
		: m_count(std::move(count))
		, m_base(std::move(base))
	{}

	BKSGE_CONSTEXPR V base() const&
		BKSGE_REQUIRES(bksge::copy_constructible<V>)
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return std::move(m_base);
	}

private:
	template <BKSGE_REQUIRES_PARAM(ranges::not_sized_range, V2), typename ThisType>
	static BKSGE_CONSTEXPR auto
	begin_impl(ThisType* this_, bksge::detail::overload_priority<2>)
	-> bksge::counted_iterator<ranges::iterator_t<V2>>
	{
		return {ranges::begin(this_->m_base), this_->m_count};
	}

	template <BKSGE_REQUIRES_PARAM(ranges::random_access_range, V2), typename ThisType>
	static BKSGE_CONSTEXPR auto
	begin_impl(ThisType* this_, bksge::detail::overload_priority<1>)
	-> ranges::iterator_t<V2>
	{
		return ranges::begin(this_->m_base);
	}

	template <typename V2, typename ThisType>
	static BKSGE_CONSTEXPR auto
	begin_impl(ThisType* this_, bksge::detail::overload_priority<0>)
	-> bksge::counted_iterator<ranges::iterator_t<V2>>
	{
		return {ranges::begin(this_->m_base), static_cast<Difference>(this_->size())};
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto begin()
	->decltype(begin_impl<V2>(this, bksge::detail::overload_priority<2>{}))
	{
		return begin_impl<V2>(this, bksge::detail::overload_priority<2>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto begin() const
	->decltype(begin_impl<V2>(this, bksge::detail::overload_priority<2>{}))
	{
		return begin_impl<V2>(this, bksge::detail::overload_priority<2>{});
	}

private:
	template <BKSGE_REQUIRES_PARAM(ranges::not_sized_range, V2), typename ThisType>
	static BKSGE_CONSTEXPR auto
	end_impl(ThisType* this_, bksge::detail::overload_priority<2>)
	-> Sentinel<bksge::is_const<ThisType>::value>
	{
		return Sentinel<bksge::is_const<ThisType>::value>{ranges::end(this_->m_base)};
	}

	template <BKSGE_REQUIRES_PARAM(ranges::random_access_range, V2), typename ThisType>
	static BKSGE_CONSTEXPR auto
	end_impl(ThisType* this_, bksge::detail::overload_priority<1>)
	-> ranges::iterator_t<V2>
	{
		return ranges::begin(this_->m_base) + this_->size();
	}

	template <typename V2, typename ThisType>
	static BKSGE_CONSTEXPR auto
	end_impl(ThisType*, bksge::detail::overload_priority<0>)
	-> bksge::default_sentinel_t
	{
		return bksge::default_sentinel;
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto end()
	->decltype(end_impl<V2>(this, bksge::detail::overload_priority<2>{}))
	{
		return end_impl<V2>(this, bksge::detail::overload_priority<2>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, V2, V const)>
	BKSGE_CONSTEXPR auto end() const
	->decltype(end_impl<V2>(this, bksge::detail::overload_priority<2>{}))
	{
		return end_impl<V2>(this, bksge::detail::overload_priority<2>{});
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto size()
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::min(ranges::size(m_base),
			static_cast<decltype(ranges::size(m_base))>(m_count));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::sized_range, V2, V const)>
	BKSGE_CONSTEXPR auto size() const
	->decltype(ranges::size(std::declval<V2>()))
	{
		return ranges::min(ranges::size(m_base),
			static_cast<decltype(ranges::size(m_base))>(m_count));
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
take_view(Range&&, ranges::range_difference_t<Range>)
-> take_view<views::all_t<Range>>;

#endif

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(T),
	take_view<T>);

namespace views
{

namespace detail
{

struct take_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename T>
	BKSGE_CONSTEXPR auto operator()(Range&& r, T&& n) const
	-> take_view<views::all_t<Range>>
	{
		return {std::forward<Range>(r), std::forward<T>(n)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::take_fn> take{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_TAKE_VIEW_HPP
