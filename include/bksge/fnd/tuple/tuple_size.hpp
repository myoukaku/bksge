/**
 *	@file	tuple_size.hpp
 *
 *	@brief	tuple_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_SIZE_HPP
#define BKSGE_FND_TUPLE_TUPLE_SIZE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::tuple_size;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/config.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <cstddef>

namespace bksge
{

template <typename T>
struct tuple_size;

template <typename... Elements>
struct tuple_size<bksge::tuple<Elements...>>
	: public bksge::integral_constant<std::size_t, sizeof...(Elements)> {};

template <typename T>
struct tuple_size<T const>
	: public tuple_size<T> {};

template <typename T>
struct tuple_size<T volatile>
	: public tuple_size<T> {};

template <typename T>
struct tuple_size<T const volatile>
	: public tuple_size<T> {};

}	// namespace bksge

#endif

#include <cstddef>

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR std::size_t
tuple_size_v = bksge::tuple_size<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_TUPLE_SIZE_HPP
