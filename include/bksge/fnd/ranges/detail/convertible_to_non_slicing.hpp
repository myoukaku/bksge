/**
 *	@file	convertible_to_non_slicing.hpp
 *
 *	@brief	convertible_to_non_slicing の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP
#define BKSGE_FND_RANGES_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP

#include <bksge/fnd/ranges/detail/not_same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept convertible_to_non_slicing =
	bksge::convertible_to<From, To> &&
	!(
		bksge::is_pointer<bksge::decay_t<From>>::value &&
		bksge::is_pointer<bksge::decay_t<To>>::value   &&
		ranges::detail::not_same_as<
			bksge::remove_pointer_t<bksge::decay_t<From>>,
			bksge::remove_pointer_t<bksge::decay_t<To>>>
	);

#else

template <typename From, typename To>
using convertible_to_non_slicing = bksge::conjunction<
	bksge::convertible_to<From, To>,
	bksge::negation<bksge::conjunction<
		bksge::is_pointer<bksge::decay_t<From>>,
		bksge::is_pointer<bksge::decay_t<To>>,
		ranges::detail::not_same_as<
			bksge::remove_pointer_t<bksge::decay_t<From>>,
			bksge::remove_pointer_t<bksge::decay_t<To>>>
	>>
>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP
