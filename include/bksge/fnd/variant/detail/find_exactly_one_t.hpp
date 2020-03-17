/**
 *	@file	find_exactly_one_t.hpp
 *
 *	@brief	find_exactly_one_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_FIND_EXACTLY_ONE_T_HPP
#define BKSGE_FND_VARIANT_DETAIL_FIND_EXACTLY_ONE_T_HPP

#include <bksge/fnd/variant/detail/find_index.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

namespace find_exactly_one_t_detail
{

template <typename T, typename... Types>
struct find_exactly_one_checked
{
	static BKSGE_CONSTEXPR std::size_t value = find_index<T, Types...>::value;
	static_assert(value != not_found, "type not found in type list");
	static_assert(value != ambiguous, "type occurs more than once in type list");
};

template <typename T>
struct find_exactly_one_checked<T>
{
	static_assert(!bksge::is_same<T, T>::value, "type not in empty type list");
};

}	// namespace find_exactly_one_t_detail

template <typename T, typename... Types>
struct find_exactly_one_t
	: public find_exactly_one_t_detail::find_exactly_one_checked<T, Types...> {};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_FIND_EXACTLY_ONE_T_HPP
