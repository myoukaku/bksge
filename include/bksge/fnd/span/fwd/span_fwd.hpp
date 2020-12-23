/**
 *	@file	span_fwd.hpp
 *
 *	@brief	span の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_FWD_SPAN_FWD_HPP
#define BKSGE_FND_SPAN_FWD_SPAN_FWD_HPP

#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

template <typename T, bksge::size_t Extent = bksge::dynamic_extent>
class span;

}	// namespace bksge

#endif // BKSGE_FND_SPAN_FWD_SPAN_FWD_HPP
