/**
 *	@file	has_virtual_destructor.hpp
 *
 *	@brief	has_virtual_destructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define BKSGE_FND_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief		型Tが仮想デストラクタを持っているか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	has_virtual_destructorは、型Tが仮想デストラクタを持っていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct has_virtual_destructor
	: public detail::constant_wrapper<
		std::has_virtual_destructor<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool has_virtual_destructor_v = has_virtual_destructor<T>::value;

#endif

}	// namespace bksge

//#include <bksge/fnd/type_traits/inl/has_virtual_destructor_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
