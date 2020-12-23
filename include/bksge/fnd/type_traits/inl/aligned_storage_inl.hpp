/**
 *	@file	aligned_storage_inl.hpp
 *
 *	@brief	aligned_storage の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_ALIGNED_STORAGE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_ALIGNED_STORAGE_INL_HPP

#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <bksge::size_t Len, typename T>
union align_type
{
	T val;
	char pad[Len];
};

template <bksge::size_t Len, typename... Types>
struct aligned_storage_helper_impl;

template <bksge::size_t Len, typename T>
struct aligned_storage_helper_impl<Len, T>
{
	static const bksge::size_t value = BKSGE_ALIGNOF(T);
	using type = align_type<Len, T>;
};

template <bksge::size_t Len, typename T, typename... Rest>
struct aligned_storage_helper_impl<Len, T, Rest...>
	: public bksge::conditional_t<
		BKSGE_ALIGNOF(T) <= Len,
		aligned_storage_helper_impl<Len, T>,
		aligned_storage_helper_impl<Len, Rest...>
	>
{};

template <bksge::size_t Len>
using aligned_storage_helper =
	aligned_storage_helper_impl<
		Len,
		std::max_align_t,
		long long,
		long,
		int,
		short,
		char
	>;

template <bksge::size_t Len>
struct default_alignment
{
	static_assert(Len != 0, "");

	static const bksge::size_t value =
		aligned_storage_helper<Len>::value;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_ALIGNED_STORAGE_INL_HPP
