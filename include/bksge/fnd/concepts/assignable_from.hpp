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
#include <bksge/fnd/type_traits/bool_constant.hpp>
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

#endif

namespace detail
{

template <typename Lhs, typename Rhs>
struct assignable_from_t_impl
{
private:
	template <typename L, typename R>
	static auto test(int) -> bksge::bool_constant<
		bksge::is_lvalue_reference<L>::value &&
		bksge::common_reference_with_t<detail::cref<L>, detail::cref<R>>::value &&
		bksge::same_as_t<L, decltype(bksge::declval<L>() = bksge::declval<R&&>())>::value
	>;

	template <typename L, typename R>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Lhs, Rhs>(0));
};

}	// namespace detail

template <typename Lhs, typename Rhs>
struct assignable_from_t
	: public detail::assignable_from_t_impl<Lhs, Rhs>::type
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_ASSIGNABLE_FROM_HPP
