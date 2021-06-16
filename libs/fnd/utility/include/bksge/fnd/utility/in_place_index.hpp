/**
 *	@file	in_place_index.hpp
 *
 *	@brief	in_place_index を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_IN_PLACE_INDEX_HPP
#define BKSGE_FND_UTILITY_IN_PLACE_INDEX_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

#if BKSGE_CXX_STANDARD >= 17

#include <utility>

namespace bksge
{

using std::in_place_index_t;
using std::in_place_index;

}	// namespace bksge

#else	// BKSGE_CXX_STANDARD >= 17

namespace bksge
{

// in_place_index_t
template <bksge::size_t I>
struct in_place_index_t
{
	explicit in_place_index_t() = default;
};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <bksge::size_t I>
BKSGE_STATIC_CONSTEXPR bksge::in_place_index_t<I> in_place_index{};

#endif	// defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace bksge

#endif	// BKSGE_CXX_STANDARD >= 17

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>

// is_in_place_index

namespace bksge
{

namespace detail
{

template <typename T>
struct is_in_place_index_impl
	: public bksge::false_type
{};

template <bksge::size_t I>
struct is_in_place_index_impl<bksge::in_place_index_t<I>>
	: public bksge::true_type
{};

}	// namespace detail

template <typename T>
using is_in_place_index =
	detail::is_in_place_index_impl<bksge::remove_cvref_t<T>>;

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_IN_PLACE_INDEX_HPP
