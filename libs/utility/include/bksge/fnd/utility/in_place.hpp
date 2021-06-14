/**
 *	@file	in_place.hpp
 *
 *	@brief	in_place を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_IN_PLACE_HPP
#define BKSGE_FND_UTILITY_IN_PLACE_HPP

#include <bksge/fnd/config.hpp>

#if BKSGE_CXX_STANDARD >= 17

#include <utility>

namespace bksge
{

using std::in_place_t;
using std::in_place;

}	// namespace bksge

#else

namespace bksge
{

struct in_place_t
{
	explicit in_place_t() = default;
};

BKSGE_STATIC_CONSTEXPR bksge::in_place_t in_place{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_IN_PLACE_HPP
