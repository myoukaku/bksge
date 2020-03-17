/**
 *	@file	get.hpp
 *
 *	@brief	get の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_GET_HPP
#define BKSGE_FND_VARIANT_GET_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::get;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

/**
 *	@brief		インデックスを指定して要素にアクセスする
 *
 *	@tparam		I		アクセスするインデックス
 *	@tparam		Types
 *
 *	@param		v		アクセスするvariant
 *
 *	@exception	v.index() == I でないとき、bad_variant_accessを投げる
 *
 *	@return		v.index() == I なら、variant内の値への参照
 */
template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>>&
get(variant<Types...>& v);

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>>&&
get(variant<Types...>&& v);

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&
get(variant<Types...> const& v);

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&&
get(variant<Types...> const&& v);

/**
 *	@brief		型を指定して要素にアクセスする
 *
 *	@tparam		T		アクセスする型
 *	@tparam		Types
 *
 *	@param		v		アクセスするvariant
 *
 *	@exception	vが型Tを保持していないとき、bad_variant_accessを投げる
 *
 *	@return		vが型Tを保持しているなら、variant内の値への参照
 *
 *	@note		T は Types... の中に一度だけ現れなければならない
 */
template <typename T, typename... Types>
BKSGE_CONSTEXPR T&
get(variant<Types...>& v);

template <typename T, typename... Types>
BKSGE_CONSTEXPR T&&
get(variant<Types...>&& v);

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&
get(variant<Types...> const& v);

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&&
get(variant<Types...> const&& v);

}	// namespace bksge

#include <bksge/fnd/variant/inl/get_inl.hpp>

#endif

#endif // BKSGE_FND_VARIANT_GET_HPP
