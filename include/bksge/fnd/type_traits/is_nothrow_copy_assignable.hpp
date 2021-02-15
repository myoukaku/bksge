/**
 *	@file	is_nothrow_copy_assignable.hpp
 *
 *	@brief	is_nothrow_copy_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがコピー代入可能で、かつ代入操作が例外を投げないかを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_copy_assignableは、型Tが例外を投げない保証のもとにコピー代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	以下の条件がtrueである場合に、例外を投げないコピー代入が可能であると見なされる：
 *	・参照可能な型Tに対しては、is_nothrow_assignable<T&, T const&>::value == trueと同じ結果となり、
 *	　それ以外はfalseと見なされる。
 *	・参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	  ・オブジェクト型
 *	  ・CV修飾されていない、もしくは参照修飾されていない関数型
 *	  ・参照修飾されている型
 */
template <typename T>
struct is_nothrow_copy_assignable
	: public detail::constant_wrapper<
		std::is_nothrow_copy_assignable<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP
