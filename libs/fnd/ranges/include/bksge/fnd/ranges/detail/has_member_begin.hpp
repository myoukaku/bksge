﻿/**
 *	@file	has_member_begin.hpp
 *
 *	@brief	has_member_begin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_BEGIN_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_BEGIN_HPP

#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_begin =
	requires(T& t)
	{
		{ decay_copy(t.begin()) } -> bksge::input_or_output_iterator;
	};

#else

template <typename T>
struct has_member_begin_impl
{
private:
	template <typename U,
		typename B = decltype(decay_copy(bksge::declval<U&>().begin()))
	>
	static auto test(int) -> bksge::input_or_output_iterator<B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_begin = typename has_member_begin_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_BEGIN_HPP
