/**
 *	@file	is_trivially_move_assignable.hpp
 *
 *	@brief	is_trivially_move_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tがトリビアルにムーブ代入可能か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_trivially_move_assignableは、型Tがトリビアルにムーブ代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	以下の条件がtrueである場合に、トリビアルにムーブ代入可能であると見なされる：
 *	・参照可能な型Tに対しては、is_trivially_assignable<T&, T&&>::value == trueと同じ結果となり、
 *	　それ以外はfalseと見なされる。
 *	・参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	  ・オブジェクト型
 *	  ・CV修飾されていない、もしくは参照修飾されていない関数型
 *	  ・参照修飾されている型
 */
template <typename T>
struct is_trivially_move_assignable;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivially_move_assignable_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP
