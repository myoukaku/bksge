/**
 *	@file	find_index.hpp
 *
 *	@brief	find_index の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_FIND_INDEX_HPP
#define BKSGE_FND_VARIANT_DETAIL_FIND_INDEX_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

static BKSGE_CONSTEXPR std::size_t not_found = static_cast<std::size_t>(-1);
static BKSGE_CONSTEXPR std::size_t ambiguous = not_found - 1;

namespace find_index_detail
{

template <std::size_t Result, std::size_t I, typename T, typename... Types>
struct find_index_impl;

template <std::size_t Result, std::size_t I, typename T, typename T0, typename... Types>
struct find_index_impl<Result, I, T, T0, Types...>
{
	static std::size_t const value =
		bksge::is_same<T, T0>::value ?
			Result != not_found ?
				ambiguous :
				find_index_impl<I, I + 1, T, Types...>::value :
			find_index_impl<Result, I + 1, T, Types...>::value;
};

template <std::size_t Result, std::size_t I, typename T>
struct find_index_impl<Result, I, T>
{
	static std::size_t const value = Result;
};

}	// namespace find_index_detail

template <typename T, typename... Types>
struct find_index
{
	static std::size_t const value =
		find_index_detail::find_index_impl<not_found, 0, T, Types...>::value;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_FIND_INDEX_HPP
