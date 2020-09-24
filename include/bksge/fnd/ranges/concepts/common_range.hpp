/**
 *	@file	common_range.hpp
 *
 *	@brief	common_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_COMMON_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_COMMON_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept common_range =
	ranges::range<T> &&
	bksge::same_as<ranges::iterator_t<T>, ranges::sentinel_t<T>>;

template <typename T>
using is_common_range = bksge::bool_constant<common_range<T>>;

#else

template <typename T>
struct common_range_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::range<U>,
			bksge::same_as<ranges::iterator_t<U>, ranges::sentinel_t<U>>
		>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using common_range = typename common_range_impl<T>::type;

template <typename T>
using is_common_range = common_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_COMMON_RANGE_HPP
