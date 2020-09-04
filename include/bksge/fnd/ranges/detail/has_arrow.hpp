/**
 *	@file	has_arrow.hpp
 *
 *	@brief	has_arrow の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_ARROW_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_ARROW_HPP

#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
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
concept has_arrow =
	bksge::input_iterator<It> &&
	(bksge::is_pointer<It>::value || requires(It it) { it.operator->(); });

#else

template <typename It>
struct has_arrow_impl
{
private:
	template <typename U, typename = decltype(bksge::declval<U>().operator->())>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = bksge::conjunction<
		bksge::input_iterator<It>,
		bksge::disjunction<
			bksge::is_pointer<It>,
			decltype(test<It>(0))
		>
	>;
};

template <typename It>
using has_arrow = typename has_arrow_impl<It>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_ARROW_HPP
