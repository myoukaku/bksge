/**
 *	@file	exactly_once.hpp
 *
 *	@brief	exactly_once の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_EXACTLY_ONCE_HPP
#define BKSGE_FND_VARIANT_DETAIL_EXACTLY_ONCE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/tuple/tuple_count.hpp>
#include <tuple>

namespace bksge
{

namespace variant_detail
{

template <typename T, typename... Types>
using exactly_once = bksge::bool_constant<bksge::tuple_count<T, std::tuple<Types...>>::value == 1>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_EXACTLY_ONCE_HPP
