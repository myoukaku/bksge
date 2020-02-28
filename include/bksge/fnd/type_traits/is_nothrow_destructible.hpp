/**
 *	@file	is_nothrow_destructible.hpp
 *
 *	@brief	is_nothrow_destructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが破棄でき、かつそのデストラクタが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_destructibleは、型Tが例外を投げない保証のもとに破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_nothrow_destructible
	: public detail::constant_wrapper<
		std::is_nothrow_destructible<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
