/**
 *	@file	variant_move_constructor.hpp
 *
 *	@brief	variant_move_constructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_CONSTRUCTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_CONSTRUCTOR_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/valueless_t.hpp>
#include <bksge/fnd/variant/detail/variant_constructor.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Traits, trait_enum = Traits::move_constructible_trait>
class variant_move_constructor;

#define BKSGE_VARIANT_MOVE_CONSTRUCTOR(move_constructible_trait, move_constructor)   \
template <typename... Types>                                                         \
class variant_move_constructor<variant_traits<Types...>, move_constructible_trait>   \
	: public variant_constructor<variant_traits<Types...>>                           \
{                                                                                    \
	using base_type = variant_constructor<variant_traits<Types...>>;                 \
                                                                                     \
public:                                                                              \
	using base_type::base_type;                                                      \
	using base_type::operator=;                                                      \
																	                 \
	variant_move_constructor(variant_move_constructor const&) = default;             \
	move_constructor                                                                 \
	~variant_move_constructor() = default;                                           \
	variant_move_constructor& operator=(variant_move_constructor const&) = default;  \
	variant_move_constructor& operator=(variant_move_constructor&&) = default;       \
}

BKSGE_VARIANT_MOVE_CONSTRUCTOR(
	trait_enum::TriviallyAvailable,
	variant_move_constructor(variant_move_constructor&& that) = default;
);

BKSGE_VARIANT_MOVE_CONSTRUCTOR(
	trait_enum::Available,
	variant_move_constructor(variant_move_constructor&& that)
		BKSGE_NOEXCEPT_IF(bksge::conjunction<bksge::is_nothrow_move_constructible<Types>...>::value)
		: variant_move_constructor(valueless_t{})
	{
		this->generic_construct(*this, bksge::move(that));
	}
);

BKSGE_VARIANT_MOVE_CONSTRUCTOR(
	trait_enum::Unavailable,
	variant_move_constructor(variant_move_constructor&&) = delete;
);

#undef BKSGE_VARIANT_MOVE_CONSTRUCTOR

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_CONSTRUCTOR_HPP
