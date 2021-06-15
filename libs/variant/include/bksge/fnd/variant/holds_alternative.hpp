/**
 *	@file	holds_alternative.hpp
 *
 *	@brief	holds_alternative の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_HOLDS_ALTERNATIVE_HPP
#define BKSGE_FND_VARIANT_HOLDS_ALTERNATIVE_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_USE_STD_VARIANT)

namespace bksge
{

using std::holds_alternative;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		variant が 指定した型を保持しているかどうか取得する
 *
 *	@tparam		T
 *	@tparam		Types
 *
 *	@param		v		調査するvariant
 *
 *	@return		v が 型Tを保持していたらtrue
 */
template <typename T, typename... Types>
BKSGE_CONSTEXPR bool
holds_alternative(variant<Types...> const& v) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/variant/inl/holds_alternative_inl.hpp>

#endif

#endif // BKSGE_FND_VARIANT_HOLDS_ALTERNATIVE_HPP
