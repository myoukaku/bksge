/**
 *	@file	enable_default_constructor.hpp
 *
 *	@brief	enable_default_constructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DETAIL_ENABLE_DEFAULT_CONSTRUCTOR_HPP
#define BKSGE_FND_DETAIL_ENABLE_DEFAULT_CONSTRUCTOR_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

struct enable_default_constructor_tag
{
	explicit BKSGE_CONSTEXPR enable_default_constructor_tag() = default;
};

template <bool DefaultConstructible, typename Tag = void>
struct enable_default_constructor
{
	BKSGE_CONSTEXPR enable_default_constructor()                                  BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR enable_default_constructor(enable_default_constructor const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR enable_default_constructor(enable_default_constructor&&)      BKSGE_NOEXCEPT = default;
	enable_default_constructor& operator=(enable_default_constructor const&)      BKSGE_NOEXCEPT = default;
	enable_default_constructor& operator=(enable_default_constructor&&)           BKSGE_NOEXCEPT = default;

	// Can be used in other ctors.
	BKSGE_CONSTEXPR explicit enable_default_constructor(enable_default_constructor_tag) {}
};

template <typename Tag>
struct enable_default_constructor<false, Tag>
{
	BKSGE_CONSTEXPR enable_default_constructor()                                  BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR enable_default_constructor(enable_default_constructor const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR enable_default_constructor(enable_default_constructor&&)      BKSGE_NOEXCEPT = default;
	enable_default_constructor& operator=(enable_default_constructor const&)      BKSGE_NOEXCEPT = default;
	enable_default_constructor& operator=(enable_default_constructor&&)           BKSGE_NOEXCEPT = default;

	// Can be used in other ctors.
	BKSGE_CONSTEXPR explicit enable_default_constructor(enable_default_constructor_tag) {}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_DETAIL_ENABLE_DEFAULT_CONSTRUCTOR_HPP
