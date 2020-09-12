/**
 *	@file	drop_while_view.hpp
 *
 *	@brief	ranges::drop_while_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_DROP_WHILE_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_DROP_WHILE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/views/all.hpp>
#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/ranges/detail/cached_position.hpp>
//#include <bksge/fnd/ranges/detail/box.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/algorithm/ranges/find_if_not.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/functional/cref.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
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
class drop_while_view : public ranges::view_interface<drop_while_view<V, Pred>>
{
private:
	V m_base = V();
//	ranges::detail::box<Pred> m_pred;
	Pred m_pred;
	BKSGE_NO_UNIQUE_ADDRESS ranges::detail::cached_position<V> m_cached_begin;

public:
	BKSGE_CONSTEXPR drop_while_view() = default;

	BKSGE_CONSTEXPR
	drop_while_view(V base, Pred pred)
		: m_base(bksge::move(base))
		, m_pred(bksge::move(pred))
	{ }

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
//		return *m_pred;
		return m_pred;
	}

	BKSGE_CXX14_CONSTEXPR auto begin()
	-> ranges::iterator_t<V>
	{
		if (m_cached_begin.has_value())
		{
			return m_cached_begin.get(m_base);
		}

		auto it = ranges::find_if_not(
			ranges::begin(m_base),
			ranges::end(m_base),
			bksge::cref(pred()));

		m_cached_begin.set(m_base, it);
		return it;
	}

	BKSGE_CXX14_CONSTEXPR auto end()
	-> ranges::sentinel_t<V>
	{
		return ranges::end(m_base);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range, typename Pred>
drop_while_view(Range&&, Pred)
-> drop_while_view<views::all_t<Range>, Pred>;

#endif

namespace views
{

namespace detail
{

struct drop_while_fn
{
	template <BKSGE_REQUIRES_PARAM(ranges::viewable_range, Range), typename Pred>
	BKSGE_CONSTEXPR auto operator()(Range&& r, Pred&& p) const
	-> drop_while_view<views::all_t<Range>, Pred>
	{
		return {bksge::forward<Range>(r), bksge::forward<Pred>(p)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::range_adaptor<views::detail::drop_while_fn> drop_while{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_DROP_WHILE_VIEW_HPP
