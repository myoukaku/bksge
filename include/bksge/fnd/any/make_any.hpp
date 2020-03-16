/**
 *	@file	make_any.hpp
 *
 *	@brief	make_any 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_MAKE_ANY_HPP
#define BKSGE_FND_ANY_MAKE_ANY_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<any>)
#include <any>
#endif

#if defined(__cpp_lib_any) && (__cpp_lib_any >= 201606)

namespace bksge
{

using std::make_any;

}	// namespace bksge

#else

#include <bksge/fnd/any/any.hpp>
#include <initializer_list>

namespace bksge
{

template <typename T, typename... Args>
any make_any(Args&&... args);

template <typename T, typename U, typename... Args>
any make_any(std::initializer_list<U> il, Args&&... args);

}	// namespace bksge

#include <bksge/fnd/any/inl/make_any_inl.hpp>

#endif

#endif // BKSGE_FND_ANY_MAKE_ANY_HPP
