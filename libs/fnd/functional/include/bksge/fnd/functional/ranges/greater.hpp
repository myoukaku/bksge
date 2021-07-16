/**
 *	@file	greater.hpp
 *
 *	@brief	ranges::greater クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_RANGES_GREATER_HPP
#define BKSGE_FND_FUNCTIONAL_RANGES_GREATER_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/detail/less_builtin_ptr_cmp.hpp>
#include <bksge/fnd/concepts/totally_ordered_with.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

/**
 *	@brief	ranges::greater
 */
struct greater
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		bksge::totally_ordered_with<T, U> ||
		detail::less_builtin_ptr_cmp<U, T>
#else
	template <typename T, typename U,
		typename = bksge::enable_if_t<
			bksge::totally_ordered_with<T, U>::value ||
			detail::less_builtin_ptr_cmp<U, T>::value
		>
	>
#endif
	BKSGE_CONSTEXPR bool operator()(T&& t, U&& u) const
		BKSGE_NOEXCEPT_IF_EXPR(std::declval<U>() < std::declval<T>())
	{
		return bksge::ranges::less{}(bksge::forward<U>(u), bksge::forward<T>(t));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_RANGES_GREATER_HPP
