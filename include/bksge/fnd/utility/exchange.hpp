/**
 *	@file	exchange.hpp
 *
 *	@brief	exchange を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_EXCHANGE_HPP
#define BKSGE_FND_UTILITY_EXCHANGE_HPP

#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	値を書き換え、書き換え前の値を返す
 *
 *	@tparam	T
 *	@tparam	U
 *
 *	T はムーブ構築可能でなければならない。
 *	U から T へムーブ代入可能でなければならない。
 *
 *	@param	obj			値を書き換えるオブジェクト
 *	@param	new_value	objに代入する値
 *
 *	@return	この関数を呼び出す前のobjの値を返す
 */
template <typename T, typename U = T>
inline BKSGE_CXX14_CONSTEXPR T
exchange(T& obj, U&& new_value)
{
    T old_value = bksge::move(obj);
    obj = bksge::forward<U>(new_value);
    return old_value;
}

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_EXCHANGE_HPP
