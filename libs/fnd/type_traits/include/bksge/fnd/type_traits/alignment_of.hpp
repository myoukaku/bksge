﻿/**
 *	@file	alignment_of.hpp
 *
 *	@brief	alignment_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define BKSGE_FND_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief		型Tのアラインメントを取得する
 *
 *	@tparam		T	取得する型
 *
 *	@require	型Tに対してalignof(T)が有効であること。
 *
 *	alignof(T)で得られたbksge::size_t型の値を、メンバ定数valueとして定義する。
 *	Tが配列型の場合、要素の型のアラインメントを取得します。
 *	Tが参照型の場合、参照している型のアラインメントを取得します。
 */
template <typename T>
struct alignment_of
	: public detail::constant_wrapper<
		std::alignment_of<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bksge::size_t alignment_of_v = alignment_of<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ALIGNMENT_OF_HPP
