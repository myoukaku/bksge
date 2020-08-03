/**
 *	@file	equality_comparable_with.hpp
 *
 *	@brief	equality_comparable_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
#define BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP

#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept equality_comparable_with =
	bksge::equality_comparable<T> &&
	bksge::equality_comparable<U> &&
	bksge::common_reference_with<detail::cref<T>, detail::cref<U>> &&
	bksge::equality_comparable<bksge::common_reference_t<detail::cref<T>, detail::cref<U>>> &&
	detail::weakly_eq_cmp_with<T, U>;

#else

namespace detail
{

template <typename T, typename U>
struct equality_comparable_with_impl
{
private:
	template <typename T2, typename U2>
	static auto test(int) -> bksge::conjunction<
		bksge::equality_comparable<T2>,
		bksge::equality_comparable<U2>,
		bksge::common_reference_with<detail::cref<T2>, detail::cref<U2>>,
		bksge::equality_comparable<bksge::common_reference_t<detail::cref<T2>, detail::cref<U2>>>,
		detail::weakly_eq_cmp_with<T2, U2>>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using equality_comparable_with =
	typename detail::equality_comparable_with_impl<T, U>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
