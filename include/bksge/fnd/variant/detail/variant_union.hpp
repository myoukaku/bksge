/**
 *	@file	variant_union.hpp
 *
 *	@brief	variant_union の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_UNION_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_UNION_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/valueless_t.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <trait_enum DestructibleTrait, std::size_t Index, typename... Types>
union variant_union;

template <trait_enum DestructibleTrait, std::size_t Index>
union variant_union<DestructibleTrait, Index> {};

#define BKSGE_VARIANT_UNION(destructible_trait, destructor)                          \
template <std::size_t Index, typename T, typename... Types>                          \
union variant_union<destructible_trait, Index, T, Types...>                          \
{                                                                                    \
public:                                                                              \
	explicit BKSGE_CONSTEXPR                                                         \
	variant_union(valueless_t) BKSGE_NOEXCEPT : m_dummy{} {}                         \
                                                                                     \
	template <typename... Args>                                                      \
	explicit BKSGE_CONSTEXPR                                                         \
	variant_union(bksge::in_place_index_t<0>, Args&&... args)                        \
		: m_head(bksge::in_place, bksge::forward<Args>(args)...) {}                  \
																			         \
	template <std::size_t I, typename... Args>                                       \
	explicit BKSGE_CONSTEXPR                                                         \
	variant_union(bksge::in_place_index_t<I>, Args&&... args)                        \
		: m_tail(bksge::in_place_index_t<I - 1>{}, bksge::forward<Args>(args)...) {} \
																			         \
	variant_union(variant_union const&) = default;                                   \
	variant_union(variant_union&&) = default;                                        \
																			         \
	destructor                                                                       \
																			         \
	variant_union& operator=(variant_union const&) = default;                        \
	variant_union& operator=(variant_union&&) = default;                             \
																			         \
	using head_type = variant_alt<Index, T>;                                         \
	using tail_type = variant_union<destructible_trait, Index + 1, Types...>;        \
																			         \
public:                                                                              \
	char m_dummy;                                                                    \
	head_type m_head;                                                                \
	tail_type m_tail;                                                                \
}

BKSGE_VARIANT_UNION(trait_enum::TriviallyAvailable, ~variant_union() = default;);
BKSGE_VARIANT_UNION(trait_enum::Available,          ~variant_union() {});
BKSGE_VARIANT_UNION(trait_enum::Unavailable,        ~variant_union() = delete;);

#undef BKSGE_VARIANT_UNION

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_UNION_HPP
