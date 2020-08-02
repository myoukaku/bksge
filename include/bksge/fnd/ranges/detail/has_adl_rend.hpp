/**
 *	@file	has_adl_rend.hpp
 *
 *	@brief	has_adl_rend の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_ADL_REND_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_ADL_REND_HPP

#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if 0
void rend(auto&) = delete;
void rend(const auto&) = delete;
#else
template <typename T> void rend(T&) = delete;
template <typename T> void rend(const T&) = delete;
#endif

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_rend =
	bksge::detail::class_or_enum<bksge::remove_reference_t<T>> &&
	requires(T& t)
	{
		{ decay_copy(rend(t)) } -> bksge::sentinel_for<decltype(ranges::rbegin(t))>;
	};

#else

template <typename T>
struct has_adl_rend_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		bksge::detail::class_or_enum_t<bksge::remove_reference_t<T>>,
		bksge::sentinel_for<
			decltype(decay_copy(rend(bksge::declval<U&>()))),
			decltype(ranges::rbegin(bksge::declval<U&>()))
		>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_rend = typename has_adl_rend_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_ADL_REND_HPP
