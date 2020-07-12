/**
 *	@file	invocable.hpp
 *
 *	@brief	invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_INVOCABLE_HPP
#define BKSGE_FND_CONCEPTS_INVOCABLE_HPP

#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept invocable = bksge::is_invocable<Fn, Args...>::value;

#endif

template <typename Fn, typename... Args>
struct invocable_t : public bksge::is_invocable<Fn, Args...> {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_INVOCABLE_HPP
