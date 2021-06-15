/**
 *	@file	wstring_view.hpp
 *
 *	@brief	wstring_view クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_WSTRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_WSTRING_VIEW_HPP

#include <bksge/fnd/string_view/basic_string_view.hpp>

namespace bksge
{

using wstring_view = bksge::basic_string_view<wchar_t>;

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_WSTRING_VIEW_HPP
