/**
 *	@file	u16string.hpp
 *
 *	@brief	u16string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_U16STRING_HPP
#define BKSGE_FND_STRING_U16STRING_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
using u16string = bksge::basic_string<char16_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_U16STRING_HPP
