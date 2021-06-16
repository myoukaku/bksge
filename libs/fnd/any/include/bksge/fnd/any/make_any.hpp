/**
 *	@file	make_any.hpp
 *
 *	@brief	make_any 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_MAKE_ANY_HPP
#define BKSGE_FND_ANY_MAKE_ANY_HPP

#include <bksge/fnd/any/config.hpp>

#if defined(BKSGE_USE_STD_ANY)

namespace bksge
{

using std::make_any;

}	// namespace bksge

#else

#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/initializer_list.hpp>

namespace bksge
{

template <typename T, typename... Args>
any make_any(Args&&... args);

template <typename T, typename U, typename... Args>
any make_any(bksge::initializer_list<U> il, Args&&... args);

}	// namespace bksge

#include <bksge/fnd/any/inl/make_any_inl.hpp>

#endif

#endif // BKSGE_FND_ANY_MAKE_ANY_HPP
