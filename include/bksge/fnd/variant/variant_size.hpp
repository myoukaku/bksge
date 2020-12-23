/**
 *	@file	variant_size.hpp
 *
 *	@brief	variant_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VARIANT_SIZE_HPP
#define BKSGE_FND_VARIANT_VARIANT_SIZE_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::variant_size;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
using std::variant_size_v;
#endif

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	variantの要素数を取得
 */
template <typename T>
struct variant_size;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR bksge::size_t
variant_size_v = variant_size<T>::value;

#endif

template <typename T>
struct variant_size<T const>
	: public bksge::variant_size<T> {};

template <typename T>
struct variant_size<T volatile>
	: public bksge::variant_size<T> {};

template <typename T>
struct variant_size<T const volatile>
	: public bksge::variant_size<T> {};

template <typename... Types>
struct variant_size<variant<Types...>>
	: public bksge::integral_constant<bksge::size_t, sizeof...(Types)> {};

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_VARIANT_SIZE_HPP
