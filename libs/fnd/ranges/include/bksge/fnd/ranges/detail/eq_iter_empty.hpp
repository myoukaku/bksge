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
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
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
concept eq_iter_empty =
	requires(T&& t)
	{
		{ ranges::begin(std::forward<T>(t)) } -> bksge::forward_iterator;
		bool(ranges::begin(std::forward<T>(t)) == ranges::end(std::forward<T>(t)));
	};

#else

template <typename T>
struct eq_iter_empty_impl
{
private:
	template <typename U,
		typename B = decltype(ranges::begin(std::declval<U&&>())),
		typename = bksge::enable_if_t<bksge::forward_iterator<B>::value>,
		typename = decltype(bool(ranges::begin(std::declval<U&&>()) == ranges::end(std::declval<U&&>())))
	>
	static auto test(int) -> bksge::true_type;

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
