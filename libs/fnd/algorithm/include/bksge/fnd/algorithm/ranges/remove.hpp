/**
 *	@file	remove.hpp
 *
 *	@brief	ranges::remove の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REMOVE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REMOVE_HPP

#include <bksge/fnd/algorithm/ranges/remove_if.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct remove_fn
{
private:
	template <typename T>
	struct Pred
	{
		T const& m_value;

		template <typename U>
		constexpr bool operator()(U&& arg) const
		{
			return std::forward<U>(arg) == m_value;
		}
	};

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::permutable Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<Iter, Proj>,
			T const*
		>
#else
	template <
		typename Iter,
		typename Sent,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::permutable<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<Iter, Proj>,
				T const*
			>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(
		Iter first, Sent last, T const& value, Proj proj = {}) const
	{
		auto pred = Pred<T>{value};
		return ranges::remove_if(
			first, last,
			std::move(pred),
			std::move(proj));
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range,
		typename T,
		typename Proj = bksge::identity
	>
	requires
		bksge::permutable<ranges::iterator_t<Range>> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<ranges::iterator_t<Range>, Proj>,
			T const*
		>
#else
	template <
		typename Range,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::permutable<ranges::iterator_t<Range>>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<ranges::iterator_t<Range>, Proj>,
				T const*
			>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, T const& value, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR remove_fn remove{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REMOVE_HPP
