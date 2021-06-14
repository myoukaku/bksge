/**
 *	@file	ref_view.hpp
 *
 *	@brief	ref_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_REF_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_REF_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/not_same_as.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/range_size_t.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/empty.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <ranges::range Range>
requires bksge::is_object<Range>::value
#else
template <typename Range,
	typename = bksge::enable_if_t<bksge::conjunction<
		ranges::range<Range>,
		bksge::is_object<Range>
	>::value>
>
#endif
class ref_view : public ranges::view_interface<ref_view<Range>>
{
private:
	Range* m_r = nullptr;

	static void Fun(Range&); // not defined
	static void Fun(Range&&) = delete;

public:
	BKSGE_CONSTEXPR ref_view() BKSGE_NOEXCEPT = default;

	template <BKSGE_REQUIRES_PARAM_2(detail::not_same_as, ref_view, T)
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::convertible_to<T, Range&>::value>
		, typename = decltype(Fun(bksge::declval<T>()))
#endif
	>
	BKSGE_REQUIRES(
		bksge::convertible_to<T, Range&> &&
		requires { Fun(bksge::declval<T>()); })
	BKSGE_CONSTEXPR ref_view(T&& t)
		: m_r(bksge::addressof(static_cast<Range&>(bksge::forward<T>(t))))
	{}

	BKSGE_CONSTEXPR Range& base() const
	{
		return *m_r;
	}

	BKSGE_CONSTEXPR ranges::iterator_t<Range> begin() const
	{
		return ranges::begin(*m_r);
	}

	BKSGE_CONSTEXPR ranges::sentinel_t<Range> end() const
	{
		return ranges::end(*m_r);
	}

	BKSGE_CONSTEXPR bool empty() const
		BKSGE_REQUIRES(requires { ranges::empty(*m_r); })
	{
		return ranges::empty(*m_r);
	}

	template <typename R2 = Range,
		typename = bksge::enable_if_t<
			ranges::is_sized_range<R2>::value
		>
	>
	BKSGE_CONSTEXPR auto size() const
	->decltype(ranges::size(bksge::declval<R2 const&>()))
	{
		return ranges::size(*m_r);
	}

	template <typename R2 = Range,
		typename = bksge::enable_if_t<
			ranges::is_contiguous_range<R2>::value
		>
	>
	BKSGE_CONSTEXPR auto data() const
	->decltype(ranges::data(bksge::declval<R2 const&>()))
	{
		return ranges::data(*m_r);
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Range>
ref_view(Range&) -> ref_view<Range>;

#endif

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, ref_view<T>);

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_REF_VIEW_HPP
