/**
 *	@file	variant_copy_assignment.hpp
 *
 *	@brief	variant_copy_assignment の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_ASSIGNMENT_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_ASSIGNMENT_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/variant_move_assignment.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Traits, trait_enum = Traits::copy_assignable_trait>
class variant_copy_assignment;

#define BKSGE_VARIANT_COPY_ASSIGNMENT(copy_assignable_trait, copy_assignment)   \
template <typename... Types>                                                    \
class variant_copy_assignment<variant_traits<Types...>, copy_assignable_trait>  \
	: public variant_move_assignment<variant_traits<Types...>>                  \
{                                                                               \
	using base_type = variant_move_assignment<variant_traits<Types...>>;        \
                                                                                \
public:                                                                         \
	using base_type::base_type;                                                 \
	using base_type::operator=;                                                 \
																		        \
	variant_copy_assignment(variant_copy_assignment const&) = default;          \
	variant_copy_assignment(variant_copy_assignment&&) = default;               \
	~variant_copy_assignment() = default;                                       \
	copy_assignment                                                             \
	variant_copy_assignment& operator=(variant_copy_assignment&&) = default;    \
}

BKSGE_VARIANT_COPY_ASSIGNMENT(
	trait_enum::TriviallyAvailable,
	variant_copy_assignment& operator=(variant_copy_assignment const& that) = default;
);

BKSGE_VARIANT_COPY_ASSIGNMENT(
	trait_enum::Available,
	variant_copy_assignment& operator=(variant_copy_assignment const& that)
	{
		this->generic_assign(that);
		return *this;
	}
);

BKSGE_VARIANT_COPY_ASSIGNMENT(
	trait_enum::Unavailable,
	variant_copy_assignment& operator=(variant_copy_assignment const&) = delete;
);

#undef BKSGE_VARIANT_COPY_ASSIGNMENT

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_ASSIGNMENT_HPP
