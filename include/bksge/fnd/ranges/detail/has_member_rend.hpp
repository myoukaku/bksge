/**
 *	@file	has_member_rend.hpp
 *
 *	@brief	has_member_rend の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_REND_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_REND_HPP

#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
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

template <typename T>
concept has_member_rend =
	requires(T& t)
	{
		{ decay_copy(t.rend()) } -> bksge::sentinel_for<decltype(ranges::rbegin(t))>;
	};

#else

template <typename T>
struct has_member_rend_impl
{
private:
	template <typename U>
	static auto test(int)
		-> bksge::sentinel_for<
			decltype(decay_copy(bksge::declval<U&>().rend())),
			decltype(ranges::rbegin(bksge::declval<U&>()))
		>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_rend = typename has_member_rend_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_REND_HPP
