/**
 *	@file	bit_cast.hpp
 *
 *	@brief	bit_cast 関数テンプレートを定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_BIT_CAST_HPP
#define BKSGE_FND_BIT_BIT_CAST_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>)
#include <bit>
#endif

#if defined(__cpp_lib_bit_cast) && (__cpp_lib_bit_cast >= 201806)

namespace bksge
{

using std::bit_cast;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <cstring>		// memcpy

namespace bksge
{

/**
 *	@brief	ビットレベルの再解釈キャスト
 *
 *	@tparam	To		キャスト先の型
 *	@tparam	From	キャスト元の型
 *
 *	@param	src		キャストする値
 *
 *	@return	srcのビット値を維持したまま型Toの値を返す
 *
 *	以下の条件のいずれかを満たさない場合、この関数はオーバーロード解決の候補から除外される：
 *	・sizeof(To) == sizeof(From)であること
 *	・is_trivially_copyable_v<To> == trueであること
 *	・is_trivially_copyable_v<From> == trueであること
 *
 *	型ToとFrom、およびその全てのサブオブジェクトが以下の条件を全て満たす場合、本関数はconstexpr関数として評価される：
 *	・is_union_v<T> == false
 *	・is_pointer_v<T> == false
 *	・is_member_pointer_v<T> == false
 *	・is_volatile_v<T> == false
 *	・Tが参照の非静的メンバ変数を持たないこと
 */
template <
	typename To,
	typename From,
	typename = bksge::enable_if_t<
		sizeof(To) == sizeof(From) &&
		bksge::is_trivially_copyable<To>::value &&
		bksge::is_trivially_copyable<From>::value
	>
>
inline To bit_cast(From const& src) BKSGE_NOEXCEPT
{
	// TODO constexpr対応
	To dst;
	std::memcpy(&dst, &src, sizeof(To));
	return dst;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_BIT_BIT_CAST_HPP
