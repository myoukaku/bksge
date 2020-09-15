/**
 *	@file	tiny_range.hpp
 *
 *	@brief	tiny_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_TINY_RANGE_HPP
#define BKSGE_FND_RANGES_DETAIL_TINY_RANGE_HPP

#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <auto>
struct require_constant;

template <typename Range>
concept tiny_range =
	ranges::sized_range<Range> &&
	requires { typename require_constant<bksge::remove_reference_t<Range>::size()>; } &&
	(bksge::remove_reference_t<Range>::size() <= 1);

template <typename Range>
using is_tiny_range = bksge::bool_constant<tiny_range<Range>>;

#else

template <typename Range>
struct tiny_range_impl
{
private:
	template <typename U, typename = bksge::enable_if_t<ranges::sized_range<U>::value>>
	static auto test(int) -> bksge::bool_constant<(bksge::remove_reference_t<U>::size() <= 1)>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Range>(0));
};

template <typename Range>
using tiny_range = typename tiny_range_impl<Range>::type;

template <typename Range>
using is_tiny_range = tiny_range<Range>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_TINY_RANGE_HPP
