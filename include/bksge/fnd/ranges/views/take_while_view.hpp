/**
 *	@file	take_while_view.hpp
 *
 *	@brief	take_while_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_TAKE_WHILE_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_TAKE_WHILE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/detail/maybe_const_t.hpp>
#include <bksge/fnd/ranges/detail/box.hpp>
#include <bksge/fnd/ranges/detail/simple_view.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::view V, typename Pred>
requires
	ranges::input_range<V> &&
	bksge::is_object<Pred>::value &&
	bksge::indirect_unary_predicate<Pred const, ranges::iterator_t<V>>
#else
template <
	typename V, typename Pred,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::view<V>,
		ranges::input_range<V>,
		bksge::is_object<Pred>,
		bksge::indirect_unary_predicate<Pred const, ranges::iterator_t<V>>
	>::value>
>
#endif
class take_while_view : public ranges::view_interface<take_while_view<V, Pred>>
{
	template <bool Const>
	struct Sentinel
	{
	private:
		using Base = ranges::detail::maybe_const_t<Const, V>;
		using Iterator = ranges::iterator_t<Base>;

		ranges::sentinel_t<Base> m_end  = {};
		Pred const*              m_pred = nullptr;

	public:
		BKSGE_CONSTEXPR Sentinel() = default;

		BKSGE_CONSTEXPR explicit
		Sentinel(ranges::sentinel_t<Base> end, Pred const* pred)
			: m_end(end)
			, m_pred(pred)
		{}

		template <bool C2 = Const,
			typename = bksge::enable_if_t<
				C2 &&
				bksge::is_convertible_to<
					ranges::sentinel_t<V>,
					ranges::sentinel_t<Base>>::value>>
		BKSGE_CONSTEXPR
		Sentinel(Sentinel<!Const> s)
			: m_end(s.m_end)
			, m_pred(s.m_pred)
		{}

		BKSGE_CONSTEXPR ranges::sentinel_t<Base>
		base() const
		{
			return m_end;
		}

		friend BKSGE_CONSTEXPR bool
		operator==(ranges::iterator_t<Base> const& lhs, Sentinel const& rhs)
		{
			return rhs.m_end == lhs || !bksge::invoke(*rhs.m_pred, *lhs);
		}

		template <bool OtherConst = !Const,
			typename Base2 = ranges::detail::maybe_const_t<OtherConst, V>,
			typename = bksge::enable_if_t<
				bksge::is_sentinel_for<
					ranges::sentinel_t<Base>,
					ranges::iterator_t<Base2>
				>::value>>
		friend BKSGE_CONSTEXPR bool
		operator==(ranges::iterator_t<Base2> const& lhs, Sentinel const& rhs)
		{
			return rhs.m_end == lhs || !bksge::invoke(*rhs.m_pred, *lhs);
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend BKSGE_CONSTEXPR bool
		operator!=(Iterator const& lhs, Sentinel const& rhs)
		{
			return !(lhs == rhs);
		}

		friend BKSGE_CONSTEXPR bool
		operator==(Sentinel const& lhs, Iterator const& rhs)
		{
			return rhs == lhs;
		}

		friend BKSGE_CONSTEXPR bool
		operator!=(Sentinel const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
		}
#endif

		friend Sentinel<!Const>;
	};

	BKSGE_NO_UNIQUE_ADDRESS ranges::detail::box<Pred> m_pred;
	V m_base = {};

public:
	BKSGE_CONSTEXPR take_while_view() = default;

	BKSGE_CONSTEXPR
	take_while_view(V base, Pred pred)
		: m_pred(bksge::move(pred))
		, m_base(bksge::move(base))
	{}

	BKSGE_CONSTEXPR V base() const&
		BKSGE_REQUIRES(bksge::copy_constructible<V>)
	{
		return m_base;
	}

	BKSGE_CXX14_CONSTEXPR V base() &&
	{
		return bksge::move(m_base);
	}

	BKSGE_CONSTEXPR Pred const& pred() const
	{
		return *m_pred;
	}
	
	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto begin()
	-> ranges::iterator_t<V2>
	{
		return ranges::begin(m_base);
	}

	template <
		typename V2 = V const,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_range<V2>,
			bksge::is_indirect_unary_predicate<Pred const, ranges::iterator_t<V2>>
		>::value>
	>
	BKSGE_CONSTEXPR auto begin() const
	-> ranges::iterator_t<V2>
	{
		return ranges::begin(m_base);
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::detail::not_simple_view, V2, V)>
	BKSGE_CXX14_CONSTEXPR auto end()
	-> Sentinel<false>
	{
		return Sentinel<false>(ranges::end(m_base), bksge::addressof(pred()));
	}

	template <
		typename V2 = V const,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::is_range<V2>,
			bksge::is_indirect_unary_predicate<Pred const, ranges::iterator_t<V2>>
		>::value>
	>
	BKSGE_CONSTEXPR auto end() const
	-> Sentinel<true>
	{
		return Sentinel<true>(ranges::end(m_base), bksge::addressof(pred()));
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range, typename Pred>
take_while_view(Range&&, Pred)
-> take_while_view<views::all_t<Range>, Pred>;

#endif

namespace views
{

namespace detail
{

struct take_while_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename Pred>
	BKSGE_CONSTEXPR auto operator()(Range&& r, Pred&& p) const
	-> take_while_view<views::all_t<Range>, Pred>
	{
		return {bksge::forward<Range>(r), bksge::forward<Pred>(p)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::take_while_fn> take_while{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_TAKE_WHILE_VIEW_HPP
