/**
 *	@file	iter_swap.hpp
 *
 *	@brief	iter_swap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_ITER_SWAP_HPP
#define BKSGE_FND_ITERATOR_RANGES_ITER_SWAP_HPP

#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_movable_storable.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/concepts/swappable_with.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

namespace ranges
{

namespace iter_swap_detail
{

#if defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920)
void iter_swap();
#elif 0
void iter_swap(auto, auto) = delete;
#else
template <typename It1, typename It2>
void iter_swap(It1, It2) = delete;
#endif

template <typename X, typename Y>
BKSGE_CXX14_CONSTEXPR bksge::iter_value_t<X>
iter_exchange_move(X&& x, Y&& y)
noexcept(
	noexcept(bksge::iter_value_t<X>(bksge::ranges::iter_move(x))) &&
	noexcept(*x = bksge::ranges::iter_move(y))
)
{
	bksge::iter_value_t<X> old(bksge::ranges::iter_move(x));
	*x = bksge::ranges::iter_move(y);
	return old;
}

struct iter_swap_fn
{
private:
	template <typename I1, typename I2
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::detail::class_or_enum<bksge::remove_cvref_t<I1>>::value ||
			bksge::detail::class_or_enum<bksge::remove_cvref_t<I2>>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires
		bksge::detail::class_or_enum<bksge::remove_cvref_t<I1>> ||
		bksge::detail::class_or_enum<bksge::remove_cvref_t<I2>>
#endif
	static BKSGE_CXX14_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, I1&& i1, I2&& i2)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(iter_swap(std::forward<I1>(i1), std::forward<I2>(i2)))

	template <typename I1, typename I2
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::indirectly_readable<I1>::value &&
			bksge::indirectly_readable<I2>::value &&
			bksge::swappable_with<bksge::iter_reference_t<I1>, bksge::iter_reference_t<I2>>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires
		bksge::indirectly_readable<I1> &&
		bksge::indirectly_readable<I2> &&
		bksge::swappable_with<bksge::iter_reference_t<I1>, bksge::iter_reference_t<I2>>
#endif
	static BKSGE_CXX14_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, I1&& i1, I2&& i2)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(ranges::swap(*i1, *i2))

	template <typename I1, typename I2
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::indirectly_movable_storable<I1, I2>::value &&
			bksge::indirectly_movable_storable<I2, I1>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires
		bksge::indirectly_movable_storable<I1, I2> &&
		bksge::indirectly_movable_storable<I2, I1>
#endif
	static BKSGE_CXX14_CONSTEXPR void
	impl(bksge::detail::overload_priority<0>, I1&& i1, I2&& i2)
		BKSGE_NOEXCEPT_IF_EXPR(*i1 = iter_exchange_move(i2, i1))
	{
		*i1 = iter_exchange_move(i2, i1);
	}

public:
	template <typename I1, typename I2>
	BKSGE_CXX14_CONSTEXPR auto operator()(I1&& i1, I2&& i2) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(impl(
			bksge::detail::overload_priority<2>{},
			std::forward<I1>(i1),
			std::forward<I2>(i2)))
};

}	// namespace iter_swap_detail

inline namespace cpo
{

// Customization point object
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
iter_swap_detail::iter_swap_fn iter_swap{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_ITERATOR_RANGES_ITER_SWAP_HPP
