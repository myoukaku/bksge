/**
 *	@file	istream_view.hpp
 *
 *	@brief	istream_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_ISTREAM_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_ISTREAM_VIEW_HPP

#include <bksge/fnd/ranges/views/basic_istream_view.hpp>
#include <bksge/fnd/istream/basic_istream.hpp>

namespace bksge
{

namespace ranges
{

template <typename Val, typename CharT, typename Traits>
basic_istream_view<Val, CharT, Traits>
istream_view(bksge::basic_istream<CharT, Traits>& s)
{
	return basic_istream_view<Val, CharT, Traits>{s};
}

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_ISTREAM_VIEW_HPP
