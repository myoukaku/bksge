/**
 *	@file	variant_construct.hpp
 *
 *	@brief	variant_construct の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_HPP

#include <bksge/fnd/variant/detail/raw_visit.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_construct_single.hpp>
#include <bksge/fnd/utility/forward.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename... Types, typename T, typename U>
void variant_construct(T&& lhs, U&& rhs)
{
	lhs.m_index = rhs.m_index;
	variant_detail::raw_visit(
		[&lhs](auto&& rhs_mem) mutable
		{
			variant_detail::variant_construct_single(
				bksge::forward<T>(lhs),
				bksge::forward<decltype(rhs_mem)>(rhs_mem));
		},
		variant_detail::variant_access::variant_cast<Types...>(bksge::forward<U>(rhs)));
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_HPP
