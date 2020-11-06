/**
 *	@file	assignable_from.hpp
 *
 *	@brief	assignable_from の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_ASSIGNABLE_FROM_HPP
#define BKSGE_FND_CONCEPTS_ASSIGNABLE_FROM_HPP

#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Lhs, typename Rhs>
concept assignable_from =
	bksge::is_lvalue_reference<Lhs>::value &&
	bksge::common_reference_with<detail::cref<Lhs>, detail::cref<Rhs>> &&
	requires(Lhs lhs, Rhs&& rhs)
	{
		{ lhs = bksge::forward<Rhs>(rhs) } -> bksge::same_as<Lhs>;
	};

template <typename Lhs, typename Rhs>
using is_assignable_from = bksge::bool_constant<assignable_from<Lhs, Rhs>>;

#else

namespace detail
{

template <typename Lhs, typename Rhs>
struct assignable_from_impl
{
private:
	template <typename L, typename R,
		typename = bksge::enable_if_t<bksge::is_lvalue_reference<L>::value>,
		typename = bksge::enable_if_t<bksge::common_reference_with<detail::cref<L>, detail::cref<R>>::value>,
		typename T = decltype(bksge::declval<L&>() = bksge::declval<R&&>())
	>
	static auto test(int) -> bksge::same_as<T, L>;

	template <typename L, typename R>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Lhs, Rhs>(0));
};

}	// namespace detail

template <typename Lhs, typename Rhs>
using assignable_from =
	typename detail::assignable_from_impl<Lhs, Rhs>::type;

template <typename Lhs, typename Rhs>
using is_assignable_from = assignable_from<Lhs, Rhs>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_ASSIGNABLE_FROM_HPP
