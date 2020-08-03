/**
 *	@file	common_with.hpp
 *
 *	@brief	common_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_COMMON_WITH_HPP
#define BKSGE_FND_CONCEPTS_COMMON_WITH_HPP

#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept common_with =
	bksge::same_as<bksge::common_type_t<T, U>, bksge::common_type_t<U, T>> &&
	requires
	{
		static_cast<bksge::common_type_t<T, U>>(bksge::declval<T>());
		static_cast<bksge::common_type_t<T, U>>(bksge::declval<U>());
	} &&
	bksge::common_reference_with<
		bksge::add_lvalue_reference_t<const T>,
		bksge::add_lvalue_reference_t<const U>
	> &&
	bksge::common_reference_with<
		bksge::add_lvalue_reference_t<bksge::common_type_t<T, U>>,
		bksge::common_reference_t<
			bksge::add_lvalue_reference_t<const T>,
			bksge::add_lvalue_reference_t<const U>
		>
	>;

#else

namespace detail
{

template <typename T, typename U>
struct common_with_impl
{
private:
	template <typename T2, typename U2,
		typename C = bksge::common_type_t<T2, U2>,
		typename = decltype(static_cast<C>(bksge::declval<T2>())),
		typename = decltype(static_cast<C>(bksge::declval<U2>()))
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<
			bksge::common_type_t<T2, U2>,
			bksge::common_type_t<U2, T2>
		>,
		bksge::common_reference_with<
			bksge::add_lvalue_reference_t<const T2>,
			bksge::add_lvalue_reference_t<const U2>
		>,
		bksge::common_reference_with<
			bksge::add_lvalue_reference_t<C>,
			bksge::common_reference_t<
				bksge::add_lvalue_reference_t<const T2>,
				bksge::add_lvalue_reference_t<const U2>
			>
		>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using common_with =
	typename detail::common_with_impl<T, U>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_COMMON_WITH_HPP
