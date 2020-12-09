/**
 *	@file	nullopt.hpp
 *
 *	@brief	nullopt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_NULLOPT_HPP
#define BKSGE_FND_OPTIONAL_NULLOPT_HPP

#include <bksge/fnd/optional/config.hpp>

#if defined(BKSGE_USE_STD_OPTIONAL)

#include <optional>

namespace bksge
{

using std::nullopt_t;
using std::nullopt;

}	// namespace bksge

#else

#if defined(BKSGE_MSVC) && (BKSGE_MSVC <= 1900)
#include <bksge/fnd/type_traits/is_literal_type.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#endif

namespace bksge
{

/// Tag type to disengage optional objects.
struct nullopt_t
{
	// Do not user-declare default constructor at all for
	// optional_value = {} syntax to work.
	// nullopt_t() = delete;

	// Used for constructing nullopt.
	enum class Construct { Token };

	// Must be constexpr for nullopt_t to be literal.
	explicit BKSGE_CONSTEXPR nullopt_t(Construct) {}
};

/// Tag to disengage optional objects.
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
nullopt_t nullopt{nullopt_t::Construct::Token};

#if defined(BKSGE_MSVC) && (BKSGE_MSVC <= 1900)

template <>
struct is_literal_type<bksge::nullopt_t>
	: public bksge::true_type
{};

#endif

}	// namespace bksge

#endif

#endif // BKSGE_FND_OPTIONAL_NULLOPT_HPP
