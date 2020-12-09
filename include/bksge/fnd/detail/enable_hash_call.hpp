/**
 *	@file	enable_hash_call.hpp
 *
 *	@brief	enable_hash_call の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DETAIL_ENABLE_HASH_CALL_HPP
#define BKSGE_FND_DETAIL_ENABLE_HASH_CALL_HPP

#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <functional>	// hash

namespace bksge
{

namespace detail
{

template <typename T, typename U = bksge::remove_const_t<T>>
struct enable_hash_call : public bksge::is_invocable<std::hash<U>, U> {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_DETAIL_ENABLE_HASH_CALL_HPP
