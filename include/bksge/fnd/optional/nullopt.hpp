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

struct nullopt_t
{
	enum class Construct { Token };
	explicit BKSGE_CONSTEXPR nullopt_t(Construct) {}
};

#if defined(BKSGE_MSVC_FULL_VER) && (192829910 <= BKSGE_MSVC_FULL_VER && BKSGE_MSVC_FULL_VER <= 192829915)
// Visual Studio 2019 version 16.9.(0-5) だと constexpr にできない(バグ?)
static const
#else
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
#endif
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
