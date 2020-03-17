/**
 *	@file	variant_traits.hpp
 *
 *	@brief	variant_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_destructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename... Types>
struct variant_traits
{
private:
	template <
		typename T,
		template <typename> class IsTriviallyAvailable,
		template <typename> class IsAvailable
	>
	struct trait
	{
		static trait_enum const value =
			IsTriviallyAvailable<T>::value ? trait_enum::TriviallyAvailable :
			IsAvailable<T>::value ?          trait_enum::Available :
											 trait_enum::Unavailable;
	};

	template <trait_enum Result, trait_enum... Traits>
	struct common_trait_impl;

	template <trait_enum Result, trait_enum T0, trait_enum... Rest>
	struct common_trait_impl<Result, T0, Rest...>
	{
		static trait_enum const value =
			static_cast<int>(T0) > static_cast<int>(Result) ?
				common_trait_impl<T0, Rest...>::value :
				common_trait_impl<Result, Rest...>::value;
	};

	template <trait_enum Result>
	struct common_trait_impl<Result>
	{
		static trait_enum const value = Result;
	};

	template <trait_enum... Traits>
	struct common_trait
	{
		static trait_enum const value =
			common_trait_impl<trait_enum::TriviallyAvailable, Traits...>::value;
	};

public:
	static BKSGE_CONSTEXPR trait_enum copy_constructible_trait =
		common_trait<
			trait<
				Types,
				bksge::is_trivially_copy_constructible,
				bksge::is_copy_constructible
			>::value...
		>::value;

	static BKSGE_CONSTEXPR trait_enum move_constructible_trait =
		common_trait<
			trait<
				Types,
				bksge::is_trivially_move_constructible,
				bksge::is_move_constructible
			>::value...
		>::value;

	static BKSGE_CONSTEXPR trait_enum copy_assignable_trait =
		common_trait<
			copy_constructible_trait,
			trait<
				Types,
				bksge::is_trivially_copy_assignable,
				bksge::is_copy_assignable
			>::value...
		>::value;

	static BKSGE_CONSTEXPR trait_enum move_assignable_trait =
		common_trait<
			move_constructible_trait,
			trait<
				Types,
				bksge::is_trivially_move_assignable,
				bksge::is_move_assignable
			>::value...
		>::value;

	static BKSGE_CONSTEXPR trait_enum destructible_trait =
		common_trait<
			trait<
				Types,
				bksge::is_trivially_destructible,
				bksge::is_destructible
			>::value...
		>::value;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_TRAITS_HPP
