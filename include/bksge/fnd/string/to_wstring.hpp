/**
 *	@file	to_wstring.hpp
 *
 *	@brief	to_wstring の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_TO_WSTRING_HPP
#define BKSGE_FND_STRING_TO_WSTRING_HPP

#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::to_wstring;

}	// namespace bksge

#else

// TODO

#endif

#endif // BKSGE_FND_STRING_TO_WSTRING_HPP
