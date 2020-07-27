/**
 *	@file	range.hpp
 *
 *	@brief	range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept range =
	requires(T& t)
	{
		ranges::begin(t);
		ranges::end(t);
	};

#else

template <typename T>
struct range_impl
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		ranges::begin(bksge::declval<U&>()),
		ranges::end(bksge::declval<U&>()),
		bksge::true_type{});

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using range = typename range_impl<T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP
