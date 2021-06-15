/**
 *	@file	u8string_view.hpp
 *
 *	@brief	u8string_view クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_U8STRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_U8STRING_VIEW_HPP

#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
using u8string_view = bksge::basic_string_view<char8_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_U8STRING_VIEW_HPP
