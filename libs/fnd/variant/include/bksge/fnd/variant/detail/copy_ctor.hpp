/**
 *	@file	copy_ctor.hpp
 *
 *	@brief	CopyCtor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_COPY_CTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_COPY_CTOR_HPP

#include <bksge/fnd/variant/detail/variant_construct.hpp>
#include <bksge/fnd/variant/detail/variant_storage.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

// The following are (Copy|Move) (ctor|assign) layers for forwarding
// triviality and handling non-trivial SMF behaviors.

template <bool, typename... Types>
struct CopyCtorBase : public variant_detail::VariantStorageAlias<Types...>
{
	using Base = variant_detail::VariantStorageAlias<Types...>;
	using Base::Base;

#if defined(BKSGE_MSVC) && BKSGE_CXX_STANDARD < 17
	CopyCtorBase() = default;
#endif

	CopyCtorBase(CopyCtorBase const& rhs)
		noexcept(variant_detail::VariantTraits<Types...>::s_nothrow_copy_ctor)
	{
		variant_detail::variant_construct<Types...>(*this, rhs);
	}

	CopyCtorBase(CopyCtorBase&&) = default;
	CopyCtorBase& operator=(CopyCtorBase const&) = default;
	CopyCtorBase& operator=(CopyCtorBase&&) = default;
};

template <typename... Types>
struct CopyCtorBase<true, Types...> : public variant_detail::VariantStorageAlias<Types...>
{
	using Base = variant_detail::VariantStorageAlias<Types...>;
	using Base::Base;
};

template <typename... Types>
using CopyCtorAlias = CopyCtorBase<variant_detail::VariantTraits<Types...>::s_trivial_copy_ctor, Types...>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_COPY_CTOR_HPP
