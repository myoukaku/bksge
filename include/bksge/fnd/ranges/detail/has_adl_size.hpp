/**
 *	@file	has_adl_size.hpp
 *
 *	@brief	has_adl_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_ADL_SIZE_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_ADL_SIZE_HPP

#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/concepts/disable_sized_range.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if 0
void size(auto&) = delete;
void size(const auto&) = delete;
#else
template <typename T> void size(T&) = delete;
template <typename T> void size(const T&) = delete;
#endif

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_size =
	bksge::detail::class_or_enum<bksge::remove_reference_t<T>> &&
	!BKSGE_RANGES_DISABLE_SIZED_RANGE(bksge::remove_cvref_t<T>) &&
	requires(T&& t)
	{
		{ decay_copy(size(bksge::forward<T>(t))) } -> bksge::integral;
	};

#else

template <typename T>
struct has_adl_size_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::bool_constant<
		bksge::detail::class_or_enum<bksge::remove_reference_t<U>>::value &&
		!BKSGE_RANGES_DISABLE_SIZED_RANGE(bksge::remove_cvref_t<U>) &&
		bksge::integral<decltype(decay_copy(size(bksge::declval<U&&>())))>::value
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_size = typename has_adl_size_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_ADL_SIZE_HPP
