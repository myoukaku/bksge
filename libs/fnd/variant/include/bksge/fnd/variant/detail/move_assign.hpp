/**
 *	@file	move_assign.hpp
 *
 *	@brief	MoveAssign の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_MOVE_ASSIGN_HPP
#define BKSGE_FND_VARIANT_DETAIL_MOVE_ASSIGN_HPP

#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/copy_assign.hpp>
#include <bksge/fnd/variant/detail/raw_idx_visit.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace variant_detail
{

template <bool, typename... Types>
struct MoveAssignBase;

template <bool B, typename... Types>
struct MoveAssignVisitor
{
	MoveAssignBase<B, Types...>*	m_this;

	template <typename RhsMem, typename RhsIndex>
	BKSGE_CXX14_CONSTEXPR void impl(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::true_type)
	{
		if (m_this->m_index == rhs_index)
		{
			variant_detail::variant_access::get_impl<rhs_index>(*m_this) = bksge::move(rhs_mem);
		}
		else
		{
			variant_detail::variant_access::variant_cast<Types...>(*m_this).template emplace<rhs_index>(bksge::move(rhs_mem));
		}
	}

	template <typename RhsMem, typename RhsIndex>
	BKSGE_CXX14_CONSTEXPR void impl(RhsMem&& /*rhs_mem*/, RhsIndex /*rhs_index*/, bksge::false_type)
	{
		m_this->reset();
	}

	template <typename RhsMem, typename RhsIndex>
	BKSGE_CXX14_CONSTEXPR void operator()(RhsMem&& rhs_mem, RhsIndex rhs_index)
	{
		impl(bksge::forward<RhsMem>(rhs_mem), rhs_index,
			bksge::bool_constant<rhs_index != bksge::variant_npos>{});
	}
};

template <typename... Types>
struct MoveAssignBase<false, Types...> : public variant_detail::CopyAssignAlias<Types...>
{
	using Base = variant_detail::CopyAssignAlias<Types...>;
	using Base::Base;

	MoveAssignBase& operator=(MoveAssignBase&& rhs)
		noexcept(variant_detail::VariantTraits<Types...>::s_nothrow_move_assign)
	{
		variant_detail::raw_idx_visit(
			MoveAssignVisitor<false, Types...>{this},
			variant_detail::variant_access::variant_cast<Types...>(rhs));

		return *this;
	}

	MoveAssignBase(MoveAssignBase const&) = default;
	MoveAssignBase(MoveAssignBase&&) = default;
	MoveAssignBase& operator=(MoveAssignBase const&) = default;
};

template <typename... Types>
struct MoveAssignBase<true, Types...> : public variant_detail::CopyAssignAlias<Types...>
{
	using Base = variant_detail::CopyAssignAlias<Types...>;
	using Base::Base;
};

template <typename... Types>
using MoveAssignAlias = MoveAssignBase<variant_detail::VariantTraits<Types...>::s_trivial_move_assign, Types...>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_MOVE_ASSIGN_HPP
