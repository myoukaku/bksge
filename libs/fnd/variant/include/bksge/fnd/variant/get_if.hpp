/**
 *	@file	get_if.hpp
 *
 *	@brief	get_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_GET_IF_HPP
#define BKSGE_FND_VARIANT_GET_IF_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_USE_STD_VARIANT)

namespace bksge
{

using std::get_if;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		インデックスを指定して要素にアクセスする(例外を投げない)
 *
 *	@tparam		I		アクセスするインデックス
 *	@tparam		Types
 *
 *	@param		pv		アクセスするvariant
 *
 *	@return		pv->index() == I なら、variant内の値へのポインタ
 *				そうでない場合、nullptr
 */
template <bksge::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>>>
get_if(variant<Types...>* pv) BKSGE_NOEXCEPT;

template <bksge::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>> const>
get_if(variant<Types...> const* pv) BKSGE_NOEXCEPT;

/**
 *	@brief		型を指定して要素にアクセスする(例外を投げない)
 *
 *	@tparam		T		アクセスする型
 *	@tparam		Types
 *
 *	@param		pv		アクセスするvariant
 *
 *	@return		variant が型Tを保持しているなら、variant内の値へのポインタ
 *				そうでない場合、nullptr
 */
template <typename T, typename... Types>
BKSGE_CONSTEXPR bksge::add_pointer_t<T>
get_if(variant<Types...>* pv) BKSGE_NOEXCEPT;

template <typename T, typename... Types>
BKSGE_CONSTEXPR bksge::add_pointer_t<T const>
get_if(variant<Types...> const* pv) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/variant/inl/get_if_inl.hpp>

#endif

#endif // BKSGE_FND_VARIANT_GET_IF_HPP
