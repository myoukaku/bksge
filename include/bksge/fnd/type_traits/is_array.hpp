/**
 *	@file	is_array.hpp
 *
 *	@brief	is_array の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_ARRAY_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_ARRAY_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_arrayは、Tが配列型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	要素数が未知(T[])だとしても判断することができる。
 *	クラステンプレートarrayは、配列型とは見なされない。
 */
template <typename T>
struct is_array
	: public detail::constant_wrapper<
		std::is_array<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_ARRAY_HPP
