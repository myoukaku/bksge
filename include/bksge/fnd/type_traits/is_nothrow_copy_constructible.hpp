/**
 *	@file	is_nothrow_copy_constructible.hpp
 *
 *	@brief	is_nothrow_copy_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがコピー構築でき、かつそのコピーコンストラクタが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_copy_constructibleは、型Tが例外を投げない保証のもとにコピー構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_nothrow_copy_constructible
	: public detail::constant_wrapper<
		std::is_nothrow_copy_constructible<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
