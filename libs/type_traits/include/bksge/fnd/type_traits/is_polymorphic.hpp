/**
 *	@file	is_polymorphic.hpp
 *
 *	@brief	is_polymorphic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_POLYMORPHIC_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_POLYMORPHIC_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが多相的なクラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない。
 *
 *	is_polymorphicは、型Tが多相的クラス (cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	多相的クラスは、少なくとも一つの仮想関数を持つクラスである。
 */
template <typename T>
struct is_polymorphic
	: public detail::constant_wrapper<
		std::is_polymorphic<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_polymorphic_v = is_polymorphic<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_POLYMORPHIC_HPP
