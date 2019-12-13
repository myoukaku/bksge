/**
 *	@file	void_t.hpp
 *
 *	@brief	void_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_VOID_T_HPP
#define BKSGE_FND_TYPE_TRAITS_VOID_T_HPP

#include <type_traits>

#if defined(__cpp_lib_void_t) && (__cpp_lib_void_t >= 201411L)

namespace bksge
{

using std::void_t;

}	// namespace bksge

#else

namespace bksge
{

namespace detail
{

template <typename... Ts>
struct make_void
{
	using type = void;
};

}	// namespace detail

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_VOID_T_HPP
