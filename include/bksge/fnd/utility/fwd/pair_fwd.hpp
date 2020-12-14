/**
 *	@file	pair_fwd.hpp
 *
 *	@brief	pair の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_FWD_PAIR_FWD_HPP
#define BKSGE_FND_UTILITY_FWD_PAIR_FWD_HPP

#include <bksge/fnd/utility/config.hpp>

#if defined(BKSGE_USE_STD_PAIR)

#include <utility>

namespace bksge
{

using std::pair;

}	// namespace bksge

#else

namespace bksge
{

template <typename T1, typename T2>
struct pair;

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_PAIR)

#endif // BKSGE_FND_UTILITY_FWD_PAIR_FWD_HPP
