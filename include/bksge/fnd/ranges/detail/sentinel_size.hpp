/**
 *	@file	sentinel_size.hpp
 *
 *	@brief	sentinel_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_SENTINEL_SIZE_HPP
#define BKSGE_FND_RANGES_DETAIL_SENTINEL_SIZE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
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
concept sentinel_size =
	requires(T&& t)
	{
		{ ranges::begin(bksge::forward<T>(t)) }
			-> bksge::forward_iterator;

		{ ranges::end(bksge::forward<T>(t)) }
			-> bksge::sized_sentinel_for<decltype(ranges::begin(bksge::forward<T>(t)))>;
	};

#else

template <typename T>
struct sentinel_size_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::forward_iterator_t<decltype(ranges::begin(bksge::declval<U&&>()))>,
		bksge::sized_sentinel_for_t<
			decltype(ranges::end(bksge::declval<U&&>())),
			decltype(ranges::begin(bksge::declval<U&&>()))
		>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using sentinel_size = typename sentinel_size_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_SENTINEL_SIZE_HPP
