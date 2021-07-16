/**
 *	@file	exchange.hpp
 *
 *	@brief	exchange を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_EXCHANGE_HPP
#define BKSGE_FND_UTILITY_EXCHANGE_HPP

#include <utility>

#if defined(__cpp_lib_exchange_function) && (__cpp_lib_exchange_function >= 201304) && \
	defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 201806)

namespace bksge
{

using std::exchange;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <utility>

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
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_EXCHANGE_HPP
