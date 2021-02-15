/**
 *	@file	is_nothrow_swappable_with.hpp
 *
 *	@brief	is_nothrow_swappable_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T, typename U>
struct is_nothrow_swappable_with
	: public detail::constant_wrapper<
		std::is_nothrow_swappable_with<T, U>
	>
{};

}	// namespace bksge

#else

namespace bksge
{

/**
 *	@brief		型T と 型U がSwap可能かつ、そのSwapが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *	@tparam		U	チェックする型
 *
 *	@require	型Tと型Uは両方とも完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_swappable_withは、型T と 型U がSwappableコンセプトを満たしており、そのswap関数が例外を投げないならtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	型TとUは参照でなければswapできないのでTとUが参照でない場合、結果はfalseとなる。
 */
template <typename T, typename U>
struct is_nothrow_swappable_with;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_swappable_with_inl.hpp>

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
