/**
 *	@file	wostringstream.hpp
 *
 *	@brief	wostringstream の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SSTREAM_WOSTRINGSTREAM_HPP
#define BKSGE_FND_SSTREAM_WOSTRINGSTREAM_HPP

#include <bksge/fnd/sstream/basic_ostringstream.hpp>

namespace bksge
{

using wostringstream = bksge::basic_ostringstream<wchar_t>;

}	// namespace bksge

#endif // BKSGE_FND_SSTREAM_WOSTRINGSTREAM_HPP
