﻿/**
 *	@file	max_size_type.hpp
 *
 *	@brief	max_size_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_MAX_SIZE_TYPE_HPP
#define BKSGE_FND_RANGES_DETAIL_MAX_SIZE_TYPE_HPP

namespace bksge
{

namespace ranges
{

namespace detail
{

#if __SIZEOF_INT128__

using max_size_type = unsigned __int128;

#else

using max_size_type = unsigned long long;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_MAX_SIZE_TYPE_HPP
