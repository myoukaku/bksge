/**
 *	@file	bitsof.hpp
 *
 *	@brief	bitsof 関数テンプレートを定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_BITSOF_HPP
#define BKSGE_FND_BIT_BITSOF_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <climits>

namespace bksge
{

/**
 *	@brief	型のビット数を取得する関数
 *
 *	コンパイラがconstexprに対応していた場合、コンパイル時定数を得ることができます。
 */
template <typename T>
inline BKSGE_CONSTEXPR bksge::size_t
bitsof(void) BKSGE_NOEXCEPT
{
	return sizeof(T) * CHAR_BIT;
}

/**
 *	@brief	型のビット数を取得する関数
 *
 *	引数から型を推測するバージョン
 */
template <typename T>
inline BKSGE_CONSTEXPR bksge::size_t
bitsof(T const&) BKSGE_NOEXCEPT
{
	return sizeof(T) * CHAR_BIT;
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_BITSOF_HPP
