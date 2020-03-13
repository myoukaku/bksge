/**
 *	@file	strcat.hpp
 *
 *	@brief	strcat 関数を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CSTRING_STRCAT_HPP
#define BKSGE_FND_CSTRING_STRCAT_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <cstring>

namespace bksge
{

inline char*
strcat(char* dest, char const* src)
{
BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4996);
	return std::strcat(dest, src);
BKSGE_WARNING_POP();
}

template <std::size_t N>  
inline char*
strcat(char (&dest)[N], char const* src)
{
	return std::strcat(dest, src);
}

}	// namespace bksge

#endif // BKSGE_FND_CSTRING_STRCAT_HPP
