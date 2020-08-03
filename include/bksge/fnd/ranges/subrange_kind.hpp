/**
 *	@file	subrange_kind.hpp
 *
 *	@brief	ranges::subrange_kind の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_SUBRANGE_KIND_HPP
#define BKSGE_FND_RANGES_SUBRANGE_KIND_HPP

namespace bksge
{

namespace ranges
{

enum class subrange_kind : bool { unsized, sized };

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_SUBRANGE_KIND_HPP
