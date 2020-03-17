/**
 *	@file	variant_move_assignment.hpp
 *
 *	@brief	variant_move_assignment の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_ASSIGNMENT_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_ASSIGNMENT_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/variant_assignment.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Traits, trait_enum = Traits::move_assignable_trait>
class variant_move_assignment;

#define BKSGE_VARIANT_MOVE_ASSIGNMENT(move_assignable_trait, move_assignment)      \
template <typename... Types>                                                       \
class variant_move_assignment<variant_traits<Types...>, move_assignable_trait>     \
	: public variant_assignment<variant_traits<Types...>>                          \
{                                                                                  \
	using base_type = variant_assignment<variant_traits<Types...>>;                \
                                                                                   \
public:                                                                            \
	using base_type::base_type;                                                    \
	using base_type::operator=;                                                    \
																	               \
	variant_move_assignment(variant_move_assignment const&) = default;             \
	variant_move_assignment(variant_move_assignment&&) = default;                  \
	~variant_move_assignment() = default;                                          \
	variant_move_assignment& operator=(variant_move_assignment const&) = default;  \
	move_assignment                                                                \
}

BKSGE_VARIANT_MOVE_ASSIGNMENT(
	trait_enum::TriviallyAvailable,
	variant_move_assignment& operator=(variant_move_assignment&& that) = default;
);

BKSGE_VARIANT_MOVE_ASSIGNMENT(
	trait_enum::Available,
	variant_move_assignment& operator=(variant_move_assignment&& that)
		BKSGE_NOEXCEPT_IF((
			bksge::conjunction<
				bksge::is_nothrow_move_constructible<Types>...,
				bksge::is_nothrow_move_assignable<Types>...
			>::value))
	{
		this->generic_assign(bksge::move(that));
		return *this;
	}
);

BKSGE_VARIANT_MOVE_ASSIGNMENT(
	trait_enum::Unavailable,
	variant_move_assignment& operator=(variant_move_assignment&&) = delete;
);

#undef BKSGE_VARIANT_MOVE_ASSIGNMENT

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_MOVE_ASSIGNMENT_HPP
