/**
 *	@file	has_member_empty.hpp
 *
 *	@brief	has_member_empty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/forward.hpp>
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
concept has_member_empty =
	requires(T&& t)
	{
		bool(bksge::forward<T>(t).empty());
	};

#else

template <typename T>
struct has_member_empty_impl
{
private:
	template <typename U>
	static auto test(int)
		-> decltype(bksge::declval<U&&>().empty(), bksge::true_type{});

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_empty = typename has_member_empty_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP
