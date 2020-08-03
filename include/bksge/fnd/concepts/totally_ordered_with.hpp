/**
 *	@file	totally_ordered_with.hpp
 *
 *	@brief	totally_ordered_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
#define BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_WITH_HPP

#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/concepts/equality_comparable_with.hpp>
#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/concepts/detail/partially_ordered_with.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept totally_ordered_with =
	bksge::totally_ordered<T> &&
	bksge::totally_ordered<U> &&
	bksge::equality_comparable_with<T, U> &&
	bksge::totally_ordered<bksge::common_reference_t<detail::cref<T>, detail::cref<U>>> &&
	detail::partially_ordered_with<T, U>;

#else

namespace detail
{

template <typename T, typename U>
struct totally_ordered_with_impl
{
private:
	template <typename T2, typename U2>
	static auto test(int) -> bksge::conjunction<
		bksge::totally_ordered<T2>,
		bksge::totally_ordered<U2>,
		bksge::equality_comparable_with<T2, U2>,
		bksge::totally_ordered<bksge::common_reference_t<detail::cref<T2>, detail::cref<U2>>>,
		detail::partially_ordered_with<T2, U2>>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using totally_ordered_with =
	typename detail::totally_ordered_with_impl<T, U>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
