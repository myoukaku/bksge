/**
 *	@file	variant_copy_constructor.hpp
 *
 *	@brief	variant_copy_constructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_CONSTRUCTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_CONSTRUCTOR_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/variant_move_constructor.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Traits, trait_enum = Traits::copy_constructible_trait>
class variant_copy_constructor;

#define BKSGE_VARIANT_COPY_CONSTRUCTOR(copy_constructible_trait, copy_constructor)   \
template <typename... Types>                                                         \
class variant_copy_constructor<variant_traits<Types...>, copy_constructible_trait>   \
	: public variant_move_constructor<variant_traits<Types...>>                      \
{                                                                                    \
	using base_type = variant_move_constructor<variant_traits<Types...>>;            \
                                                                                     \
public:                                                                              \
	using base_type::base_type;                                                      \
	using base_type::operator=;                                                      \
																		             \
	copy_constructor                                                                 \
	variant_copy_constructor(variant_copy_constructor&&) = default;                  \
	~variant_copy_constructor() = default;                                           \
	variant_copy_constructor& operator=(variant_copy_constructor const&) = default;  \
	variant_copy_constructor& operator=(variant_copy_constructor&&) = default;       \
}

BKSGE_VARIANT_COPY_CONSTRUCTOR(
	trait_enum::TriviallyAvailable,
	variant_copy_constructor(variant_copy_constructor const& that) = default;
);

BKSGE_VARIANT_COPY_CONSTRUCTOR(
	trait_enum::Available,
	variant_copy_constructor(variant_copy_constructor const& that)
		: variant_copy_constructor(valueless_t{})
	{
		this->generic_construct(*this, that);
	}
);

BKSGE_VARIANT_COPY_CONSTRUCTOR(
	trait_enum::Unavailable,
	variant_copy_constructor(variant_copy_constructor const&) = delete;
);

#undef BKSGE_VARIANT_COPY_CONSTRUCTOR

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_COPY_CONSTRUCTOR_HPP
