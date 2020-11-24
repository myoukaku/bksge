/**
 *	@file	variadic_union.hpp
 *
 *	@brief	VariadicUnion の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIADIC_UNION_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIADIC_UNION_HPP

#include <bksge/fnd/variant/detail/uninitialized.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <typename... Types>
union VariadicUnion {};

template <typename First, typename... Rest>
union VariadicUnion<First, Rest...>
{
	BKSGE_CONSTEXPR VariadicUnion()
		: m_rest()
	{}

	template <typename... Args>
	BKSGE_CONSTEXPR VariadicUnion(bksge::in_place_index_t<0>, Args&&... args)
		: m_first(bksge::in_place_index_t<0>{}, bksge::forward<Args>(args)...)
	{}

	template <std::size_t N, typename... Args>
	BKSGE_CONSTEXPR VariadicUnion(bksge::in_place_index_t<N>, Args&&... args)
		: m_rest(bksge::in_place_index_t<N-1>{}, bksge::forward<Args>(args)...)
	{}

	Uninitialized<First>   m_first;
	VariadicUnion<Rest...> m_rest;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIADIC_UNION_HPP
