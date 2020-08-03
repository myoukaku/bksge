/**
 *	@file	swappable_with.hpp
 *
 *	@brief	swappable_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SWAPPABLE_WITH_HPP
#define BKSGE_FND_CONCEPTS_SWAPPABLE_WITH_HPP

#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept swappable_with =
	bksge::common_reference_with<T, U> &&
	requires(T&& t, U&& u)
	{
		ranges::swap(static_cast<T&&>(t), static_cast<T&&>(t));
		ranges::swap(static_cast<U&&>(u), static_cast<U&&>(u));
		ranges::swap(static_cast<T&&>(t), static_cast<U&&>(u));
		ranges::swap(static_cast<U&&>(u), static_cast<T&&>(t));
	};

#else

namespace detail
{

template <typename T, typename U>
struct swappable_with_impl
{
private:
	template <typename T2, typename U2,
		typename = decltype(
			ranges::swap(bksge::declval<T2>(), bksge::declval<T2>()),
			ranges::swap(bksge::declval<U2>(), bksge::declval<U2>()),
			ranges::swap(bksge::declval<T2>(), bksge::declval<U2>()),
			ranges::swap(bksge::declval<U2>(), bksge::declval<T2>()))
	>
	static auto test(int) -> bksge::common_reference_with<T2, U2>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using swappable_with =
	typename detail::swappable_with_impl<T, U>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SWAPPABLE_WITH_HPP
