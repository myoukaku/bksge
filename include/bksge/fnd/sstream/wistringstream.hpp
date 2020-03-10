/**
 *	@file	wistringstream.hpp
 *
 *	@brief	wistringstream の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SSTREAM_WISTRINGSTREAM_HPP
#define BKSGE_FND_SSTREAM_WISTRINGSTREAM_HPP

#include <bksge/fnd/sstream/basic_istringstream.hpp>

namespace bksge
{

using wistringstream = bksge::basic_istringstream<wchar_t>;

}	// namespace bksge

#endif // BKSGE_FND_SSTREAM_WISTRINGSTREAM_HPP
