/**
 *	@file	is_array_unknown_bounds.hpp
 *
 *	@brief	is_array_unknown_bounds の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_ARRAY_UNKNOWN_BOUNDS_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_ARRAY_UNKNOWN_BOUNDS_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

/**
 *	@brief		型Tが要素数不明の配列かどうか調べる
 */
template <typename T>
struct is_array_unknown_bounds
	: public bksge::bool_constant<
		std::is_array<T>::value &&
		std::extent<T>::value == 0
	>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_ARRAY_UNKNOWN_BOUNDS_HPP
