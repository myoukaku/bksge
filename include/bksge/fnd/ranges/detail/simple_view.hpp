/**
 *	@file	simple_view.hpp
 *
 *	@brief	simple_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_SIMPLE_VIEW_HPP
#define BKSGE_FND_RANGES_DETAIL_SIMPLE_VIEW_HPP

#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Range>
concept simple_view =
	ranges::view<Range> &&
	ranges::range<Range const> &&
	bksge::same_as<ranges::iterator_t<Range>, ranges::iterator_t<Range const>> &&
	bksge::same_as<ranges::sentinel_t<Range>, ranges::sentinel_t<Range const>>;

template <typename Range>
concept not_simple_view = !simple_view<Range>;

#else

template <typename Range>
struct simple_view_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::view<U>,
		ranges::range<U const>,
		bksge::same_as<ranges::iterator_t<U>, ranges::iterator_t<U const>>,
		bksge::same_as<ranges::sentinel_t<U>, ranges::sentinel_t<U const>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Range>(0));
};

template <typename Range>
using simple_view = typename simple_view_impl<Range>::type;

template <typename Range>
using not_simple_view = bksge::negation<simple_view<Range>>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_SIMPLE_VIEW_HPP
