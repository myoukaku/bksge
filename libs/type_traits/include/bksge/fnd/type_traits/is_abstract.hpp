/**
 *	@file	is_abstract.hpp
 *
 *	@brief	is_abstract の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_ABSTRACT_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_ABSTRACT_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが抽象クラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない。
 *
 *	is_abstractは、型Tが抽象クラス (cv修飾を許容する) であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	抽象クラスとは、少なくとも一つの純粋仮想関数を持つクラスである。
 */
template <typename T>
struct is_abstract
	: public detail::constant_wrapper<
		std::is_abstract<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_abstract_v = is_abstract<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_ABSTRACT_HPP
