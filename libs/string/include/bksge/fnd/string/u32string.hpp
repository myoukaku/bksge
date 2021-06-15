/**
 *	@file	u32string.hpp
 *
 *	@brief	u32string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_U32STRING_HPP
#define BKSGE_FND_STRING_U32STRING_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
using u32string = bksge::basic_string<char32_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_U32STRING_HPP
