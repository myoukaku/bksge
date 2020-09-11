/**
 *	@file	cached_position.hpp
 *
 *	@brief	cached_position の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_CACHED_POSITION_HPP
#define BKSGE_FND_RANGES_DETAIL_CACHED_POSITION_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename Range>
struct cached_position_impl_0;

template <typename Range>
struct cached_position_impl_1
{
	BKSGE_CONSTEXPR bool has_value() const
	{
		return false;
	}

	BKSGE_CONSTEXPR ranges::iterator_t<Range>
	get(Range const&) const
	{
		return
			BKSGE_ASSERT(false),
			ranges::iterator_t<Range>{};
	}

	BKSGE_CXX14_CONSTEXPR void
	set(Range const&, ranges::iterator_t<Range> const&) const
	{}
};

template <typename Range>
struct cached_position_impl_2
{
private:
	ranges::iterator_t<Range> m_iter{};

public:
	BKSGE_CONSTEXPR bool has_value() const
	{
		return m_iter != ranges::iterator_t<Range>{};
	}

	BKSGE_CONSTEXPR ranges::iterator_t<Range>
	get(Range const&) const
	{
		return
			BKSGE_ASSERT(has_value()),
			m_iter;
	}

	BKSGE_CXX14_CONSTEXPR void
	set(Range const&, ranges::iterator_t<Range> const& it)
	{
		BKSGE_ASSERT(!has_value());
		m_iter = it;
	}
};

template <typename Range>
struct cached_position_impl_3
{
private:
	ranges::range_difference_t<Range> m_offset = -1;

public:
	BKSGE_CONSTEXPR bool has_value() const
	{
		return m_offset >= 0;
	}

	BKSGE_CONSTEXPR ranges::iterator_t<Range>
	get(Range& r) const
	{
		return
			BKSGE_ASSERT(has_value()),
			ranges::begin(r) + m_offset;
	}

	BKSGE_CXX14_CONSTEXPR void
	set(Range& r, ranges::iterator_t<Range> const& it)
	{
		BKSGE_ASSERT(!has_value());
		m_offset = it - ranges::begin(r);
	}
};

template <typename Range>
using cached_position =
	bksge::conditional_t<
		ranges::is_random_access_range<Range>::value &&
		sizeof(ranges::range_difference_t<Range>) <= sizeof(ranges::iterator_t<Range>),
		cached_position_impl_3<Range>,
	bksge::conditional_t<
		ranges::is_forward_range<Range>::value,
		cached_position_impl_2<Range>,
	bksge::conditional_t<
		ranges::is_range<Range>::value,
		cached_position_impl_1<Range>,
		cached_position_impl_0<Range>
	>>>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_CACHED_POSITION_HPP
