/**
 *	@file	aligned_storage.hpp
 *
 *	@brief	aligned_storage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define BKSGE_FND_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include <cstddef>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <std::size_t Len>
struct default_alignment;

}	// namespace detail

/**
 *	@brief		アラインメント調整された領域を作る
 *
 *	@tparam		Len		領域の大きさ
 *	@tparam		Align	領域のアラインメント
 *
 *	@require	Lenが非ゼロであること。
 *				Alignは、得ようとしてる領域の要素型Tに対するalignof(T)と同じ大きさか、
 *				もしくはデフォルト値であること。
 *
 *	aligned_storageは、領域サイズLen、アラインメントAlignで調整した未初期化領域をメンバ型typeとして定義する。
 *	メンバ型typeはPOD型となる(参照：is_pod)。
 *
 *	Alignのデフォルト値は、Lenよりも大きくない、最も厳格なアラインメント要件を持つ、
 *	C++の何らかのオブジェクト型のアラインメント値。
 */
using std::aligned_storage;

/**
 *	@brief	aligned_storageのエイリアステンプレート
 */
template <std::size_t Len, std::size_t Align = detail::default_alignment<Len>::value>
using aligned_storage_t = typename aligned_storage<Len, Align>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/aligned_storage_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_ALIGNED_STORAGE_HPP
