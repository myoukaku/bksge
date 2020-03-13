/**
 *	@file	strlen.hpp
 *
 *	@brief	strlen 関数を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CSTRING_STRLEN_HPP
#define BKSGE_FND_CSTRING_STRLEN_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

/**
 *	@brief		文字列の長さを得る
 *
 *	@param		str		ヌル終端された文字列へのポインタ
 *
 *	@return		文字列 str の長さ
 */
BKSGE_CXX14_CONSTEXPR std::size_t
strlen(char const* str);

/**
 *	@overload
 */
BKSGE_CXX14_CONSTEXPR std::size_t
strlen(wchar_t const* str);

}	// namespace bksge

#include <bksge/fnd/cstring/inl/strlen_inl.hpp>

#endif // BKSGE_FND_CSTRING_STRLEN_HPP
