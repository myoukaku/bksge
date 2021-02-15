/**
 *	@file	is_volatile.hpp
 *
 *	@brief	is_volatile の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_VOLATILE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_VOLATILE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがvolatile修飾型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_volatileは、型Tがvolatile修飾型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	volatile修飾型は、volatile および const volatile を含む。
 *
 *	参照型は、volatile修飾型でない。
 */
template <typename T>
struct is_volatile
	: public detail::constant_wrapper<
		std::is_volatile<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_volatile_v = is_volatile<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_VOLATILE_HPP
