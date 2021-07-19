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
#include <utility>

namespace bksge
{

namespace variant_detail
{

template <typename T>
struct variant_construct_t
{
	T& m_lhs;

	template <typename U>
	void operator()(U&& rhs_mem)
	{
		variant_detail::variant_construct_single(
			std::forward<T>(m_lhs),
			std::forward<U>(rhs_mem));
	}
};

template <typename... Types, typename T, typename U>
void variant_construct(T&& lhs, U&& rhs)
{
	lhs.m_index = rhs.m_index;
	variant_detail::raw_visit(
		variant_construct_t<T>{lhs},
		variant_detail::variant_access::variant_cast<Types...>(std::forward<U>(rhs)));
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCT_HPP
