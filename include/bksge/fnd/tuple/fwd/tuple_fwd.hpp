/**
 *	@file	tuple_fwd.hpp
 *
 *	@brief	tuple の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_FWD_TUPLE_FWD_HPP
#define BKSGE_FND_TUPLE_FWD_TUPLE_FWD_HPP

#include <bksge/fnd/tuple/config.hpp>

namespace bksge
{

#if defined(BKSGE_USE_STD_TUPLE)

using std::tuple;

#else

template <typename... Elements>
class tuple;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_FWD_TUPLE_FWD_HPP
