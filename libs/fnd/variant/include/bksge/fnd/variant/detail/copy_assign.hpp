/**
 *	@file	copy_assign.hpp
 *
 *	@brief	CopyAssign の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_COPY_ASSIGN_HPP
#define BKSGE_FND_VARIANT_DETAIL_COPY_ASSIGN_HPP

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/move_ctor.hpp>
#include <bksge/fnd/variant/detail/raw_idx_visit.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>

namespace bksge
{

namespace variant_detail
{

template <bool, typename... Types>
struct CopyAssignBase;

template <bool B, typename... Types>
struct CopyAssignVisitor
{
	CopyAssignBase<B, Types...>*	m_this;

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl2(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::true_type)
	{
		// The standard says this->emplace<rhs_type>(rhs_mem)
		// should be used here, but destructive_copy is
		// equivalent in this case. Either copy construction
		// doesn't throw, so destructive_copy gives strong
		// exception safety guarantee, or both copy construction
		// and move construction can throw, so emplace only gives
		// basic exception safety anyway.
		m_this->destructive_copy(static_cast<unsigned short>(rhs_index), rhs_mem);
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl2(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::false_type)
	{
		variant_detail::variant_access::variant_cast<Types...>(*m_this) =
			bksge::variant<Types...>(bksge::in_place_index_t<rhs_index>{}, rhs_mem);
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::true_type)
	{
		if (m_this->m_index == rhs_index)
		{
			variant_detail::variant_access::get_impl<rhs_index>(*m_this) = rhs_mem;
		}
		else
		{
			using rhs_type = bksge::remove_cvref_t<decltype(rhs_mem)>;
			impl2(bksge::forward<RhsMem>(rhs_mem), rhs_index, bksge::bool_constant<
				bksge::is_nothrow_copy_constructible<rhs_type>::value ||
				!bksge::is_nothrow_move_constructible<rhs_type>::value>{});
		}
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl(RhsMem&& /*rhs_mem*/, RhsIndex /*rhs_index*/, bksge::false_type)
	{
		m_this->reset();
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void operator()(RhsMem&& rhs_mem, RhsIndex rhs_index)
	{
		impl(bksge::forward<RhsMem>(rhs_mem), rhs_index,
			bksge::bool_constant<rhs_index != bksge::variant_npos>{});
	}
};

template <typename... Types>
struct CopyAssignBase<false, Types...> : public variant_detail::MoveCtorAlias<Types...>
{
	using Base = variant_detail::MoveCtorAlias<Types...>;
	using Base::Base;

	CopyAssignBase& operator=(CopyAssignBase const& rhs)
		noexcept(variant_detail::VariantTraits<Types...>::s_nothrow_copy_assign)
	{
		variant_detail::raw_idx_visit(
			CopyAssignVisitor<false, Types...>{this},
			variant_detail::variant_access::variant_cast<Types...>(rhs));

		return *this;
	}

	CopyAssignBase(CopyAssignBase const&) = default;
	CopyAssignBase(CopyAssignBase&&) = default;
	CopyAssignBase& operator=(CopyAssignBase&&) = default;
};

template <typename... Types>
struct CopyAssignBase<true, Types...> : public variant_detail::MoveCtorAlias<Types...>
{
	using Base = variant_detail::MoveCtorAlias<Types...>;
	using Base::Base;
};

template <typename... Types>
using CopyAssignAlias = CopyAssignBase<variant_detail::VariantTraits<Types...>::s_trivial_copy_assign, Types...>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_COPY_ASSIGN_HPP
