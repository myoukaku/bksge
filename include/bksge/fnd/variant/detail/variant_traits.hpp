/**
 *	@file	variant_traits.hpp
 *
 *	@brief	VariantTraits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename... Types>
struct VariantTraits
{
	static constexpr bool s_default_ctor = bksge::is_default_constructible<bksge::nth_t<0, Types...>>::value;
	static constexpr bool s_copy_ctor    = bksge::conjunction<bksge::is_copy_constructible<Types>...>::value;
	static constexpr bool s_move_ctor    = bksge::conjunction<bksge::is_move_constructible<Types>...>::value;
	static constexpr bool s_copy_assign  = s_copy_ctor && bksge::conjunction<bksge::is_copy_assignable<Types>...>::value;
	static constexpr bool s_move_assign  = s_move_ctor && bksge::conjunction<bksge::is_move_assignable<Types>...>::value;

	static constexpr bool s_trivial_dtor        = bksge::conjunction<bksge::is_trivially_destructible<Types>...>::value;
	static constexpr bool s_trivial_copy_ctor   = bksge::conjunction<bksge::is_trivially_copy_constructible<Types>...>::value;
	static constexpr bool s_trivial_move_ctor   = bksge::conjunction<bksge::is_trivially_move_constructible<Types>...>::value;
	static constexpr bool s_trivial_copy_assign = s_trivial_dtor && s_trivial_copy_ctor && bksge::conjunction<bksge::is_trivially_copy_assignable<Types>...>::value;
	static constexpr bool s_trivial_move_assign = s_trivial_dtor && s_trivial_move_ctor && bksge::conjunction<bksge::is_trivially_move_assignable<Types>...>::value;

	// The following nothrow traits are for non-trivial SMFs. Trivial SMFs
	// are always nothrow.
	static constexpr bool s_nothrow_default_ctor = bksge::is_nothrow_default_constructible<bksge::nth_t<0, Types...>>::value;
	static constexpr bool s_nothrow_copy_ctor    = false;
	static constexpr bool s_nothrow_move_ctor    = bksge::conjunction<bksge::is_nothrow_move_constructible<Types>...>::value;
	static constexpr bool s_nothrow_copy_assign  = false;
	static constexpr bool s_nothrow_move_assign  = s_nothrow_move_ctor && bksge::conjunction<bksge::is_nothrow_move_assignable<Types>...>::value;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP
