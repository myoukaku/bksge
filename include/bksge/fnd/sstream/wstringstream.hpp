/**
 *	@file	wstringstream.hpp
 *
 *	@brief	wstringstream の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SSTREAM_WSTRINGSTREAM_HPP
#define BKSGE_FND_SSTREAM_WSTRINGSTREAM_HPP

#include <bksge/fnd/sstream/basic_stringstream.hpp>

namespace bksge
{

using wstringstream = bksge::basic_stringstream<wchar_t>;

}	// namespace bksge

#endif // BKSGE_FND_SSTREAM_WSTRINGSTREAM_HPP
