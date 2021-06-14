/**
 *	@file	in_place_type.hpp
 *
 *	@brief	in_place_type を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_IN_PLACE_TYPE_HPP
#define BKSGE_FND_UTILITY_IN_PLACE_TYPE_HPP

#include <bksge/fnd/config.hpp>

#if BKSGE_CXX_STANDARD >= 17

#include <utility>

namespace bksge
{

using std::in_place_type_t;
using std::in_place_type;

}	// namespace bksge

#else	// BKSGE_CXX_STANDARD >= 17

namespace bksge
{

// in_place_type_t
template <typename T>
struct in_place_type_t
{
	explicit in_place_type_t() = default;
};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_STATIC_CONSTEXPR bksge::in_place_type_t<T> in_place_type{};

#endif	// defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace bksge

#endif	// BKSGE_CXX_STANDARD >= 17

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>

// is_in_place_type

namespace bksge
{

namespace detail
{

template <typename T>
struct is_in_place_type_impl
	: public bksge::false_type
{};

template <typename T>
struct is_in_place_type_impl<bksge::in_place_type_t<T>>
	: public bksge::true_type
{};

}	// namespace detail

template <typename T>
using is_in_place_type =
	detail::is_in_place_type_impl<bksge::remove_cvref_t<T>>;

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_IN_PLACE_TYPE_HPP
