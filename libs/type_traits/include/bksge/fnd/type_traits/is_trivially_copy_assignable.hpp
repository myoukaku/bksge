/**
 *	@file	is_trivially_copy_assignable.hpp
 *
 *	@brief	is_trivially_copy_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tがトリビアルにコピー代入可能か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_trivially_copy_assignableは、型Tがトリビアルにコピー代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	以下の条件がtrueである場合に、トリビアルにコピー代入可能であると見なされる：
 *	・参照可能な型Tに対しては、is_trivially_assignable<T&, T const&>::value == trueと同じ結果となり、
 *	　それ以外はfalseと見なされる。
 *	・参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	  ・オブジェクト型
 *	  ・CV修飾されていない、もしくは参照修飾されていない関数型
 *	  ・参照修飾されている型
 */
template <typename T>
struct is_trivially_copy_assignable;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivially_copy_assignable_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
