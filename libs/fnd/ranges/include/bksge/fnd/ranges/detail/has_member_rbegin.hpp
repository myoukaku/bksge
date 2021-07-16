/**
 *	@file	has_member_rbegin.hpp
 *
 *	@brief	has_member_rbegin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP

#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_rbegin =
	requires(T& t)
	{
		{ decay_copy(t.rbegin()) } -> bksge::input_or_output_iterator;
	};

#else

template <typename T>
struct has_member_rbegin_impl
{
private:
	template <typename U,
		typename B = decltype(decay_copy(std::declval<U&>().rbegin()))
	>
	static auto test(int) -> bksge::input_or_output_iterator<B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_rbegin = typename has_member_rbegin_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
