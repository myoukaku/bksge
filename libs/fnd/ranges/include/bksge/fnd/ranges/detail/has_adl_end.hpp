/**
 *	@file	has_adl_end.hpp
 *
 *	@brief	has_adl_end の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_ADL_END_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_ADL_END_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if 0
void end(auto&) = delete;
void end(const auto&) = delete;
#else
template <typename T> void end(T&) = delete;
template <typename T> void end(const T&) = delete;
#endif

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_end =
	bksge::detail::class_or_enum<bksge::remove_reference_t<T>> &&
	requires(T& t)
	{
		{ decay_copy(end(t)) } -> bksge::sentinel_for<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct has_adl_end_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<
			bksge::detail::class_or_enum<
				bksge::remove_reference_t<U>
			>::value>,
		typename E = decltype(decay_copy(end(std::declval<U&>()))),
		typename B = decltype(ranges::begin(std::declval<U&>()))
	>
	static auto test(int) -> bksge::sentinel_for<E, B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_end = typename has_adl_end_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_ADL_END_HPP
