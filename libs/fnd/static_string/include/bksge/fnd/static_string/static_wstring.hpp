/**
 *	@file	static_wstring.hpp
 *
 *	@brief	static_wstring の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_STRING_STATIC_WSTRING_HPP
#define BKSGE_FND_STATIC_STRING_STATIC_WSTRING_HPP

#include <bksge/fnd/static_string/basic_static_string.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t Capacity>
using static_wstring = bksge::basic_static_string<wchar_t, Capacity>;

}	// namespace bksge

#endif // BKSGE_FND_STATIC_STRING_STATIC_WSTRING_HPP
