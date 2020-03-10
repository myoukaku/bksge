/**
 *	@file	u32string_view.hpp
 *
 *	@brief	u32string_view クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_U32STRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_U32STRING_VIEW_HPP

#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
using u32string_view = bksge::basic_string_view<char32_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_U32STRING_VIEW_HPP
