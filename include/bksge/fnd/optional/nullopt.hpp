/**
 *	@file	nullopt.hpp
 *
 *	@brief	nullopt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_NULLOPT_HPP
#define BKSGE_FND_OPTIONAL_NULLOPT_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<optional>)
#include <optional>
#endif

#if defined(__cpp_lib_optional) && (__cpp_lib_optional >= 201606)

namespace bksge
{

using std::nullopt_t;
using std::nullopt;

}	// namespace bksge

#else

#if defined(_MSC_VER) && (_MSC_VER <= 1900)
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

BKSGE_STATIC_CONSTEXPR nullopt_t nullopt{ nullopt_t::Construct::Token };

// none, none_t も使えるようにエイリアスを提供する
using none_t = nullopt_t;
BKSGE_STATIC_CONSTEXPR none_t none = nullopt;

#if defined(_MSC_VER) && (_MSC_VER <= 1900)

template <>
struct is_literal_type<bksge::nullopt_t>
	: public bksge::true_type
{};

#endif

}	// namespace bksge

#endif

#endif // BKSGE_FND_OPTIONAL_NULLOPT_HPP
