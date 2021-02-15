/**
 *	@file	extent.hpp
 *
 *	@brief	extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_EXTENT_HPP
#define BKSGE_FND_TYPE_TRAITS_EXTENT_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	配列型のI番目の次元の要素数を取得する。
 *
 *	@tparam	T
 *	@tparam	I
 *
 *	型Tが配列型であり、配列の次元数がIより大きい場合、
 *	I次元目の要素数をメンバ定数valueとして定義する。
 *	型Tが配列型ではない、もしくは配列の次元数がI以下の場合、
 *	値0をメンバ定数valueとして定義する。
 */
template <typename T, unsigned int I = 0>
struct extent
	: public detail::constant_wrapper<
		std::extent<T, I>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, unsigned int I = 0>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bksge::size_t extent_v = extent<T, I>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_EXTENT_HPP
