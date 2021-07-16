/**
 *	@file	has_member_end.hpp
 *
 *	@brief	has_member_end の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_END_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_END_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_end =
	requires(T& t)
	{
		{ decay_copy(t.end()) } -> bksge::sentinel_for<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct has_member_end_impl
{
private:
	template <typename U,
		typename E = decltype(decay_copy(std::declval<U&>().end())),
		typename B = decltype(ranges::begin(std::declval<U&>()))
	>
	static auto test(int) -> bksge::sentinel_for<E, B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_end = typename has_member_end_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_END_HPP
