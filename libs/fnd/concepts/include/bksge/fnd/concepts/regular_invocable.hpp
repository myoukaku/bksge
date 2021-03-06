﻿/**
 *	@file	regular_invocable.hpp
 *
 *	@brief	regular_invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_REGULAR_INVOCABLE_HPP
#define BKSGE_FND_CONCEPTS_REGULAR_INVOCABLE_HPP

#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept regular_invocable = bksge::invocable<Fn, Args...>;

template <typename Fn, typename... Args>
using is_regular_invocable = bksge::bool_constant<regular_invocable<Fn, Args...>>;

#else

template <typename Fn, typename... Args>
using regular_invocable = bksge::invocable<Fn, Args...>;

template <typename Fn, typename... Args>
using is_regular_invocable = regular_invocable<Fn, Args...>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_REGULAR_INVOCABLE_HPP
