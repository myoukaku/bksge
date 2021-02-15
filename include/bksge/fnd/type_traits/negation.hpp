/**
 *	@file	negation.hpp
 *
 *	@brief	negation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_NEGATION_HPP
#define BKSGE_FND_TYPE_TRAITS_NEGATION_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace bksge
{

using std::negation;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

/**
 *	@brief		コンパイル時の論理否定
 *
 *	@tparam		B
 *
 *	integral_constant<bool, !B::value> と同じ
 */
template <typename B>
struct negation : public bksge::bool_constant<!B::value> {};

}	// namespace bksge

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename B>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool negation_v = negation<B>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_NEGATION_HPP
