/**
 *	@file	find_unambiguous_index_sfinae.hpp
 *
 *	@brief	find_unambiguous_index_sfinae の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_FIND_UNAMBIGUOUS_INDEX_SFINAE_HPP
#define BKSGE_FND_VARIANT_DETAIL_FIND_UNAMBIGUOUS_INDEX_SFINAE_HPP

#include <bksge/fnd/variant/detail/find_index.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <std::size_t I>
struct find_unambiguous_index_sfinae_impl
	: public bksge::integral_constant<std::size_t, I> {};

template <>
struct find_unambiguous_index_sfinae_impl<not_found> {};

template <>
struct find_unambiguous_index_sfinae_impl<ambiguous> {};

template <typename T, typename... Types>
struct find_unambiguous_index_sfinae
	: public find_unambiguous_index_sfinae_impl<find_index<T, Types...>::value> {};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_FIND_UNAMBIGUOUS_INDEX_SFINAE_HPP
