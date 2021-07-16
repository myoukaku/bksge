/**
 *	@file	size0_empty.hpp
 *
 *	@brief	size0_empty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_SIZE0_EMPTY_HPP
#define BKSGE_FND_RANGES_DETAIL_SIZE0_EMPTY_HPP

#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/forward.hpp>
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
concept size0_empty =
	requires(T&& t)
	{
		ranges::size(bksge::forward<T>(t)) == 0;
	};

#else

template <typename T>
struct size0_empty_impl
{
private:
	template <typename U,
		typename = decltype(ranges::size(std::declval<U&&>()) == 0)
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using size0_empty = typename size0_empty_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_SIZE0_EMPTY_HPP
