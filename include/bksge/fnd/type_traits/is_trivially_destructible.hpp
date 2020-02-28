/**
 *	@file	is_trivially_destructible.hpp
 *
 *	@brief	is_trivially_destructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがトリビアルに破棄可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_trivially_destructibleは、型Tがトリビアルに破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	「トリビアルに破棄可能」とは、ユーザー定義されないデストラクタを持っているということを意味する。
 */
template <typename T>
struct is_trivially_destructible
	: public detail::constant_wrapper<
		std::is_trivially_destructible<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
