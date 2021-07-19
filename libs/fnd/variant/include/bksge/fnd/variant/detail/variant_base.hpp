/**
 *	@file	variant_base.hpp
 *
 *	@brief	VariantBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP

#include <bksge/fnd/variant/detail/move_assign.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace variant_detail
{

template <typename... Types>
struct VariantBase : public variant_detail::MoveAssignAlias<Types...>
{
	using Base = variant_detail::MoveAssignAlias<Types...>;

	constexpr
	VariantBase()
		noexcept(variant_detail::VariantTraits<Types...>::s_nothrow_default_ctor)
		: VariantBase(bksge::in_place_index_t<0>{})
	{}

	template <std::size_t N, typename... Args>
	constexpr explicit
	VariantBase(bksge::in_place_index_t<N> i, Args&&... args)
		: Base(i, std::forward<Args>(args)...)
	{}

	VariantBase(VariantBase const&)            = default;
	VariantBase(VariantBase&&)                 = default;
	VariantBase& operator=(VariantBase const&) = default;
	VariantBase& operator=(VariantBase&&)      = default;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP
