/**
 *	@file	holds_alternative_inl.hpp
 *
 *	@brief	holds_alternative の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP
#define BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/detail/exactly_once.hpp>
#include <bksge/fnd/variant/detail/index_of.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename... Types>
BKSGE_CONSTEXPR bool
holds_alternative(variant<Types...> const& v) BKSGE_NOEXCEPT
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	return v.index() == variant_detail::index_of<T, Types...>::value;
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP
