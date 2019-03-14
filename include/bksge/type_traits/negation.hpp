/**
 *	@file	negation.hpp
 *
 *	@brief	negation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_NEGATION_HPP
#define BKSGE_TYPE_TRAITS_NEGATION_HPP

#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace bksge
{

using std::negation;

}	// namespace bksge

#else

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
struct negation : public std::integral_constant<bool, !B::value> {};

}	// namespace bksge

#endif

#endif // BKSGE_TYPE_TRAITS_NEGATION_HPP
