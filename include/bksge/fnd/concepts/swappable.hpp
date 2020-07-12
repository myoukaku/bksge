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
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept swappable =
	requires(T& a, T& b) { ranges::swap(a, b); };

#endif

namespace detail
{

template <typename T>
struct swappable_t_impl
{
private:
	template <typename U,
		typename = decltype(
			ranges::swap(bksge::declval<U&>(), bksge::declval<U&>()))
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
struct swappable_t
	: public detail::swappable_t_impl<T>::type {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SWAPPABLE_HPP
