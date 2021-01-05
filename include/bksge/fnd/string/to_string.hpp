/**
 *	@file	to_string.hpp
 *
 *	@brief	to_string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_TO_STRING_HPP
#define BKSGE_FND_STRING_TO_STRING_HPP

#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::to_string;

}	// namespace bksge

#else

// TODO

#endif

#endif // BKSGE_FND_STRING_TO_STRING_HPP
