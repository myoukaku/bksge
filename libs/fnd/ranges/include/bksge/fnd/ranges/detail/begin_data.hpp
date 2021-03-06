﻿/**
 *	@file	begin_data.hpp
 *
 *	@brief	begin_data の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_BEGIN_DATA_HPP
#define BKSGE_FND_RANGES_DETAIL_BEGIN_DATA_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept begin_data =
	requires(T&& t)
	{
		{ ranges::begin(bksge::forward<T>(t)) } -> bksge::contiguous_iterator;
	};

#else

template <typename T>
struct begin_data_impl
{
private:
	template <typename U, typename B = decltype(ranges::begin(bksge::declval<U>()))>
	static auto test(int) -> bksge::contiguous_iterator<B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using begin_data = typename begin_data_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_BEGIN_DATA_HPP
