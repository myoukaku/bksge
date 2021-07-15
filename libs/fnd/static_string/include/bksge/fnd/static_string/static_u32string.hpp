/**
 *	@file	static_u32string.hpp
 *
 *	@brief	static_u32string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_STRING_STATIC_U32STRING_HPP
#define BKSGE_FND_STATIC_STRING_STATIC_U32STRING_HPP

#include <bksge/fnd/static_string/basic_static_string.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
template <std::size_t Capacity>
using static_u32string = bksge::basic_static_string<char32_t, Capacity>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STATIC_STRING_STATIC_U32STRING_HPP
