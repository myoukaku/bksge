/**
 *	@file	reversable.hpp
 *
 *	@brief	reversable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_REVERSABLE_HPP
#define BKSGE_FND_RANGES_DETAIL_REVERSABLE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept reversable =
	requires(T& t)
	{
		{ ranges::begin(t) } -> bksge::bidirectional_iterator;
		{ ranges::end(t) } -> bksge::same_as<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct reversable_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::bidirectional_iterator_t<
			decltype(ranges::begin(bksge::declval<U&>()))
		>,
		bksge::same_as_t<
			decltype(ranges::end(bksge::declval<U&>())),
			decltype(ranges::begin(bksge::declval<U&>()))
		>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using reversable = typename reversable_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_REVERSABLE_HPP
