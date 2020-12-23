/**
 *	@file	strcpy.hpp
 *
 *	@brief	strcpy 関数を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CSTRING_STRCPY_HPP
#define BKSGE_FND_CSTRING_STRCPY_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <cstring>

namespace bksge
{

inline char*
strcpy(char* dest, char const* src)
{
BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4996);
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-declarations");
	return std::strcpy(dest, src);
BKSGE_WARNING_POP();
}

template <bksge::size_t N>  
inline char*
strcpy(char (&dest)[N], char const* src)
{
	return std::strcpy(dest, src);
}

}	// namespace bksge

#endif // BKSGE_FND_CSTRING_STRCPY_HPP
