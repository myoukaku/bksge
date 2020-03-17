/**
 *	@file	holds_alternative_inl.hpp
 *
 *	@brief	holds_alternative の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP
#define BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP

#include <bksge/fnd/variant/holds_alternative.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/detail/find_exactly_one_t.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR bool
holds_alternative_impl(variant<Types...> const& v) BKSGE_NOEXCEPT
{
	return v.index() == I;
}

}	// namespace variant_detail

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR bool
holds_alternative(variant<Types...> const& v) BKSGE_NOEXCEPT
{
	return variant_detail::holds_alternative_impl<
		variant_detail::find_exactly_one_t<T, Types...>::value
	>(v);
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_HOLDS_ALTERNATIVE_INL_HPP
