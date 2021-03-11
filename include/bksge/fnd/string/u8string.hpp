/**
 *	@file	u8string.hpp
 *
 *	@brief	u8string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_U8STRING_HPP
#define BKSGE_FND_STRING_U8STRING_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
using u8string = bksge::basic_string<char8_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_U8STRING_HPP
