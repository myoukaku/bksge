/**
 *	@file	eq_iter_empty.hpp
 *
 *	@brief	eq_iter_empty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
#define BKSGE_FND_RANGES_DETAIL_EQ_ITER_EMPTY_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept eq_iter_empty =
	requires(T&& t)
	{
		{ ranges::begin(bksge::forward<T>(t)) } -> bksge::forward_iterator;
		bool(ranges::begin(bksge::forward<T>(t)) == ranges::end(bksge::forward<T>(t)));
	};

#else

template <typename T>
struct eq_iter_empty_impl
{
private:
	template <typename U>
	static auto test(int) ->
		decltype(
			bool(ranges::begin(bksge::declval<U&&>()) == ranges::end(bksge::declval<U&&>())),
			bksge::forward_iterator<decltype(ranges::begin(bksge::declval<U&&>()))>{}
		);

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using eq_iter_empty = typename eq_iter_empty_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
