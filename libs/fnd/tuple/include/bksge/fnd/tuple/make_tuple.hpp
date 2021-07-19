/**
 *	@file	make_tuple.hpp
 *
 *	@brief	make_tuple の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_MAKE_TUPLE_HPP
#define BKSGE_FND_TUPLE_MAKE_TUPLE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::make_tuple;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/unwrap_ref_decay.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <typename... Types>
inline BKSGE_CONSTEXPR bksge::tuple<bksge::unwrap_ref_decay_t<Types>...>
make_tuple(Types&&... args)
{
	return bksge::tuple<bksge::unwrap_ref_decay_t<Types>...>(
		std::forward<Types>(args)...);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_TUPLE_MAKE_TUPLE_HPP
