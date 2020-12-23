/**
 *	@file	variant_storage.hpp
 *
 *	@brief	VariantStorage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_STORAGE_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_STORAGE_HPP

#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/do_visit.hpp>
#include <bksge/fnd/variant/detail/never_valueless.hpp>
#include <bksge/fnd/variant/detail/select_index_type.hpp>
#include <bksge/fnd/variant/detail/variadic_union.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/memory/destroy_at.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace variant_detail
{

// Defines index and the dtor, possibly trivial.
template <bool trivially_destructible, typename... Types>
struct VariantStorage;


template <typename... Types>
struct VariantStorage<false, Types...>
{
	constexpr
	VariantStorage()
		: m_index(static_cast<index_type>(bksge::variant_npos))
	{}

	template <bksge::size_t N, typename... Args>
	constexpr
	VariantStorage(bksge::in_place_index_t<N>, Args&&... args)
		: m_u(bksge::in_place_index<N>, bksge::forward<Args>(args)...)
		, m_index{N}
	{}

	void reset()
	{
		if (!valid()) /*[[unlikely]]*/
		{
			return;
		}

		variant_detail::do_visit<void>(
			[](auto&& this_mem) mutable
			{
				bksge::destroy_at(bksge::addressof(this_mem));
			},
			variant_detail::variant_access::variant_cast<Types...>(*this));

		m_index = static_cast<index_type>(bksge::variant_npos);
	}

	~VariantStorage()
	{
		reset();
	}

	constexpr bool valid() const noexcept
	{
		return
			variant_detail::NeverValueless<Types...>::value ||
			this->m_index != static_cast<index_type>(bksge::variant_npos);
	}

	variant_detail::VariadicUnion<Types...> m_u;
	using index_type = variant_detail::select_index_type<Types...>;
	index_type m_index;
};

template <typename... Types>
struct VariantStorage<true, Types...>
{
	constexpr
	VariantStorage()
		: m_index(static_cast<index_type>(bksge::variant_npos))
	{}

	template <bksge::size_t N, typename... Args>
	constexpr
	VariantStorage(bksge::in_place_index_t<N>, Args&&... args)
		: m_u(bksge::in_place_index<N>, bksge::forward<Args>(args)...)
		, m_index{N}
	{}

	void reset() noexcept
	{
		m_index = static_cast<index_type>(bksge::variant_npos);
	}

	constexpr bool valid() const noexcept
	{
		return
			variant_detail::NeverValueless<Types...>::value ||
			this->m_index != static_cast<index_type>(bksge::variant_npos);
	}

	variant_detail::VariadicUnion<Types...> m_u;
	using index_type = variant_detail::select_index_type<Types...>;
	index_type m_index;
};

template <typename... Types>
using VariantStorageAlias = VariantStorage<variant_detail::VariantTraits<Types...>::s_trivial_dtor, Types...>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_STORAGE_HPP
