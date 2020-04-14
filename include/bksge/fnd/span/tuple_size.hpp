﻿/**
 *	@file	tuple_size.hpp
 *
 *	@brief	tuple_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_TUPLE_SIZE_HPP
#define BKSGE_FND_SPAN_TUPLE_SIZE_HPP

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <cstddef>
#include <tuple>

namespace std
{

template <typename T, std::size_t N>
struct tuple_size<bksge::span<T, N>>
	: public bksge::integral_constant<std::size_t, N> {};

template <typename T>
struct tuple_size<bksge::span<T, bksge::dynamic_extent>>; // declared but not defined

}	// namespace std

#endif // BKSGE_FND_SPAN_TUPLE_SIZE_HPP
