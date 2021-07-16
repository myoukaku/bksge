/**
 *	@file	optional_relop_t.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_RELOP_T_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_RELOP_T_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

template <typename T>
using optional_relop_t =
	bksge::enable_if_t<bksge::is_convertible<T, bool>::value, bool>;

template <typename T, typename U>
using optional_eq_t = optional_relop_t<
	decltype(std::declval<T const&>() == std::declval<U const&>())
>;

template <typename T, typename U>
using optional_ne_t = optional_relop_t<
	decltype(std::declval<T const&>() != std::declval<U const&>())
>;

template <typename T, typename U>
using optional_lt_t = optional_relop_t<
	decltype(std::declval<T const&>() < std::declval<U const&>())
>;

template <typename T, typename U>
using optional_gt_t = optional_relop_t<
	decltype(std::declval<T const&>() > std::declval<U const&>())
>;

template <typename T, typename U>
using optional_le_t = optional_relop_t<
	decltype(std::declval<T const&>() <= std::declval<U const&>())
>;

template <typename T, typename U>
using optional_ge_t = optional_relop_t<
	decltype(std::declval<T const&>() >= std::declval<U const&>())
>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_RELOP_T_HPP
