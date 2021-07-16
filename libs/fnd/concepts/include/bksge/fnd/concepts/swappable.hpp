/**
 *	@file	swappable.hpp
 *
 *	@brief	swappable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SWAPPABLE_HPP
#define BKSGE_FND_CONCEPTS_SWAPPABLE_HPP

#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept swappable =
	requires(T& a, T& b) { ranges::swap(a, b); };

#else

namespace detail
{

template <typename T>
struct swappable_impl
{
private:
	template <typename U,
		typename = decltype(
			ranges::swap(std::declval<U&>(), std::declval<U&>()))
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using swappable =
	typename detail::swappable_impl<T>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SWAPPABLE_HPP
