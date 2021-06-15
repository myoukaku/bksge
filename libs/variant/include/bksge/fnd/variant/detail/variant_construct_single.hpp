/**
 *	@file	variant_construct_single.hpp
 *
 *	@brief	variant_construct_single の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_SINGLE_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_SINGLE_HPP

#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/forward.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename T, typename U>
void variant_construct_single_impl(T&&, U&&, bksge::true_type)
{
}

template <typename T, typename U>
void variant_construct_single_impl(T&& lhs, U&& rhs_mem, bksge::false_type)
{
	using Type = bksge::remove_reference_t<U>;
	void* storage = bksge::addressof(lhs.m_u);
	::new (storage) Type(bksge::forward<U>(rhs_mem));
}

template <typename T, typename U>
void variant_construct_single(T&& lhs, U&& rhs_mem)
{
	using Type = bksge::remove_reference_t<U>;
	variant_construct_single_impl(bksge::forward<T>(lhs), bksge::forward<U>(rhs_mem),
		bksge::is_same<Type, variant_detail::VariantCookie>{});
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_SINGLE_HPP
