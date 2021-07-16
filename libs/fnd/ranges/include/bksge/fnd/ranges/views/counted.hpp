/**
 *	@file	counted.hpp
 *
 *	@brief	counted の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_COUNTED_HPP
#define BKSGE_FND_RANGES_VIEWS_COUNTED_HPP

#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/counted_iterator.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace views
{

namespace detail
{

struct counted_fn
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES) &&	\
	defined(BKSGE_HAS_CXX17_IF_CONSTEXPR)     &&	\
	defined(BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION)

	template <BKSGE_REQUIRES_PARAM(bksge::input_or_output_iterator, Iter)>
	BKSGE_CXX14_CONSTEXPR auto
	operator()(Iter i, bksge::iter_difference_t<Iter> n) const
	{
		if constexpr (bksge::is_random_access_iterator<Iter>::value)
		{
			return ranges::subrange{i, i + n};
		}
		else
		{
			return ranges::subrange{
				bksge::counted_iterator{std::move(i), n},
				bksge::default_sentinel
			};
		}
	}

#else

private:
	template <BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter), typename Difference>
	static BKSGE_CXX14_CONSTEXPR auto
	impl(Iter i, Difference n, bksge::detail::overload_priority<1>)
	-> ranges::subrange<Iter, Iter>
	{
		return {i, i + n};
	}

	template <typename Iter, typename Difference>
	static BKSGE_CXX14_CONSTEXPR auto
	impl(Iter i, Difference n, bksge::detail::overload_priority<0>)
	-> ranges::subrange<
		bksge::counted_iterator<Iter>,
		bksge::default_sentinel_t>
	{
		return {
			bksge::counted_iterator<Iter>{std::move(i), n},
			bksge::default_sentinel
		};
	}

public:
	template <BKSGE_REQUIRES_PARAM(bksge::input_or_output_iterator, Iter)>
	BKSGE_CXX14_CONSTEXPR auto
	operator()(Iter i, bksge::iter_difference_t<Iter> n) const
	->decltype(impl(std::move(i), n, bksge::detail::overload_priority<1>{}))
	{
		return impl(std::move(i), n, bksge::detail::overload_priority<1>{});
	}

#endif
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
views::detail::counted_fn counted{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_COUNTED_HPP
