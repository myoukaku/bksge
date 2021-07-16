/**
 *	@file	move_if_noexcept.hpp
 *
 *	@brief	move_if_noexcept を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define BKSGE_FND_UTILITY_MOVE_IF_NOEXCEPT_HPP

#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

/**
 *	@brief		オブジェクトが例外を投げなければムーブする
 *
 *	@tparam		T
 *
 *	@param		x
 *
 *	@return		move(x)
 *
 *	この関数は、対象のオブジェクトが例外を投げないムーブコンストラクタを持っている場合に
 *	右辺値参照を返し、そうでなければconst左辺値参照を返す。
 */
template <typename T>
inline BKSGE_CONSTEXPR typename bksge::conditional<
	!bksge::is_nothrow_move_constructible<T>::value &&
	bksge::is_copy_constructible<T>::value,
	T const&,
	T&&
>::type
move_if_noexcept(T& x) BKSGE_NOEXCEPT
{
	return std::move(x);
}

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_MOVE_IF_NOEXCEPT_HPP
