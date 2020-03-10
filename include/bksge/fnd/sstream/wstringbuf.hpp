/**
 *	@file	wstringbuf.hpp
 *
 *	@brief	wstringbuf の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SSTREAM_WSTRINGBUF_HPP
#define BKSGE_FND_SSTREAM_WSTRINGBUF_HPP

#include <bksge/fnd/sstream/basic_stringbuf.hpp>

namespace bksge
{

using wstringbuf = bksge::basic_stringbuf<wchar_t>;

}	// namespace bksge

#endif // BKSGE_FND_SSTREAM_WSTRINGBUF_HPP
