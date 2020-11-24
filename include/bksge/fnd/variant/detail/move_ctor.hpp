/**
 *	@file	move_ctor.hpp
 *
 *	@brief	MoveCtor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_MOVE_CTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_MOVE_CTOR_HPP

#include <bksge/fnd/variant/detail/copy_ctor.hpp>
#include <bksge/fnd/variant/detail/variant_construct.hpp>
#include <bksge/fnd/variant/detail/variant_construct_single.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace variant_detail
{

template <bool, typename... Types>
struct MoveCtorBase : public variant_detail::CopyCtorAlias<Types...>
{
	using Base = variant_detail::CopyCtorAlias<Types...>;
	using Base::Base;

	MoveCtorBase(MoveCtorBase&& rhs)
		noexcept(variant_detail::VariantTraits<Types...>::s_nothrow_move_ctor)
	{
		variant_detail::variant_construct<Types...>(*this, bksge::move(rhs));
	}

	template <typename U>
	void destructive_move(unsigned short rhs_index, U&& rhs)
	{
		this->reset();
		variant_detail::variant_construct_single(*this, bksge::forward<U>(rhs));
		this->m_index = rhs_index;
	}

	template <typename U>
	void destructive_copy(unsigned short rhs_index, const U& rhs)
	{
		this->reset();
		variant_detail::variant_construct_single(*this, rhs);
		this->m_index = rhs_index;
	}

	MoveCtorBase(MoveCtorBase const&) = default;
	MoveCtorBase& operator=(MoveCtorBase const&) = default;
	MoveCtorBase& operator=(MoveCtorBase&&) = default;
};

template <typename... Types>
struct MoveCtorBase<true, Types...> : public variant_detail::CopyCtorAlias<Types...>
{
	using Base = variant_detail::CopyCtorAlias<Types...>;
	using Base::Base;

	template <typename U>
	void destructive_move(unsigned short rhs_index, U&& rhs)
	{
		this->reset();
		variant_detail::variant_construct_single(*this, bksge::forward<U>(rhs));
		this->m_index = rhs_index;
	}

	template <typename U>
	void destructive_copy(unsigned short rhs_index, const U& rhs)
	{
		this->reset();
		variant_detail::variant_construct_single(*this, rhs);
		this->m_index = rhs_index;
	}
};

template <typename... Types>
using MoveCtorAlias = MoveCtorBase<variant_detail::VariantTraits<Types...>::s_trivial_move_ctor, Types...>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_MOVE_CTOR_HPP
