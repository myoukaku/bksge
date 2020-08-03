/**
 *	@file	common_reference_with.hpp
 *
 *	@brief	common_reference_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_COMMON_REFERENCE_WITH_HPP
#define BKSGE_FND_CONCEPTS_COMMON_REFERENCE_WITH_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept common_reference_with =
	bksge::same_as<bksge::common_reference_t<T, U>, bksge::common_reference_t<U, T>> &&
	bksge::convertible_to<T, bksge::common_reference_t<T, U>> &&
	bksge::convertible_to<U, bksge::common_reference_t<T, U>>;

#else

namespace detail
{

template <typename T, typename U>
struct common_reference_with_impl
{
private:
	template <typename T2, typename U2,
		typename C = bksge::common_reference_t<T2, U2>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<C, bksge::common_reference_t<U2, T2>>,
		bksge::convertible_to<T2, C>,
		bksge::convertible_to<U2, C>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using common_reference_with =
	typename detail::common_reference_with_impl<T, U>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_COMMON_REFERENCE_WITH_HPP
