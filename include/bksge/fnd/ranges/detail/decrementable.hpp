/**
 *	@file	decrementable.hpp
 *
 *	@brief	decrementable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_DECREMENTABLE_HPP
#define BKSGE_FND_RANGES_DETAIL_DECREMENTABLE_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/iterator/concepts/incrementable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename It>
concept decrementable =
	bksge::incrementable<It> &&
	requires(It i)
	{
		{ --i } -> bksge::same_as<It&>;
		{ i-- } -> bksge::same_as<It>;
	};

template <typename It>
using is_decrementable = bksge::bool_constant<decrementable<It>>;

#else

template <typename It>
struct decrementable_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::incrementable<U>,
		bksge::same_as<decltype(--bksge::declval<U&>()), U&>,
		bksge::same_as<decltype(bksge::declval<U&>()--), U>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<It>(0));
};

template <typename It>
using decrementable = typename decrementable_impl<It>::type;

template <typename It>
using is_decrementable = decrementable<It>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_DECREMENTABLE_HPP
