/**
 *	@file	is_tuple_like.hpp
 *
 *	@brief	is_tuple_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_IS_TUPLE_LIKE_HPP
#define BKSGE_FND_TUPLE_DETAIL_IS_TUPLE_LIKE_HPP

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/array/fwd/array_fwd.hpp>
#include <bksge/fnd/utility/fwd/pair_fwd.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>

namespace bksge
{

namespace tuple_detail
{

template <typename>
struct is_tuple_like_impl : public bksge::false_type
{};

template <typename... Types>
struct is_tuple_like_impl<bksge::tuple<Types...>> : public bksge::true_type
{};

template <typename T, bksge::size_t N>
struct is_tuple_like_impl<bksge::array<T, N>> : public bksge::true_type
{};

template <typename T1, typename T2>
struct is_tuple_like_impl<bksge::pair<T1, T2>> : public bksge::true_type
{};

// Internal type trait that allows us to sfinae-protect tuple_cat.
template <typename T>
struct is_tuple_like
	: public is_tuple_like_impl<bksge::remove_cvref_t<T>>::type
{};

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_IS_TUPLE_LIKE_HPP
