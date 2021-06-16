/**
 *	@file	u16string_view.hpp
 *
 *	@brief	u16string_view クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_U16STRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_U16STRING_VIEW_HPP

#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
using u16string_view = bksge::basic_string_view<char16_t>;
#endif

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_U16STRING_VIEW_HPP
