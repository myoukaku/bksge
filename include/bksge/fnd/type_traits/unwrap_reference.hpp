/**
 *	@file	unwrap_reference.hpp
 *
 *	@brief	unwrap_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_UNWRAP_REFERENCE_HPP

#include <type_traits>

#if defined(__cpp_lib_unwrap_ref) && (__cpp_lib_unwrap_ref >= 201811)

namespace bksge
{

using std::unwrap_reference;
using std::unwrap_reference_t;

}	// namespace bksge

#else

#include <functional>

namespace bksge
{

template <typename T>
struct unwrap_reference { using type = T; };

template <typename T>
struct unwrap_reference<std::reference_wrapper<T>> { using type = T&; };

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
