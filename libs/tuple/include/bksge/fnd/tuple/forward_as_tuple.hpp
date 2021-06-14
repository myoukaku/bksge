/**
 *	@file	forward_as_tuple.hpp
 *
 *	@brief	forward_as_tuple の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_FORWARD_AS_TUPLE_HPP
#define BKSGE_FND_TUPLE_FORWARD_AS_TUPLE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::forward_as_tuple;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename... Types>
inline BKSGE_CONSTEXPR bksge::tuple<Types&&...>
forward_as_tuple(Types&&... args) noexcept
{
	return bksge::tuple<Types&&...>(bksge::forward<Types>(args)...);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_TUPLE_FORWARD_AS_TUPLE_HPP
