/**
 *	@file	static_u16string.hpp
 *
 *	@brief	static_u16string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_STRING_STATIC_U16STRING_HPP
#define BKSGE_FND_STATIC_STRING_STATIC_U16STRING_HPP

#include <bksge/fnd/static_string/basic_static_string.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
template <bksge::size_t Capacity>
using static_u16string = bksge::basic_static_string<char16_t, Capacity>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STATIC_STRING_STATIC_U16STRING_HPP
