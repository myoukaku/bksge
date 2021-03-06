﻿/**
 *	@file	exactly_once.hpp
 *
 *	@brief	exactly_once の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_EXACTLY_ONCE_HPP
#define BKSGE_FND_TUPLE_DETAIL_EXACTLY_ONCE_HPP

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/tuple_count.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace tuple_detail
{

template <typename T, typename... Types>
using exactly_once = bksge::bool_constant<
	bksge::tuple_count<T, bksge::tuple<Types...>>::value == 1>;

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_EXACTLY_ONCE_HPP
