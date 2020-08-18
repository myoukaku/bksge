/**
 *	@file	has_member_size.hpp
 *
 *	@brief	has_member_size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP

#include <bksge/fnd/ranges/concepts/disable_sized_range.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/detail/integer_like.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
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
concept has_member_size =
	!BKSGE_RANGES_DISABLE_SIZED_RANGE(bksge::remove_cvref_t<T>) &&
	requires(T&& t)
	{
		{ decay_copy(bksge::forward<T>(t).size()) } -> detail::integer_like;
	};

#else

template <typename T>
struct has_member_size_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::bool_constant<
		!BKSGE_RANGES_DISABLE_SIZED_RANGE(bksge::remove_cvref_t<U>) &&
		detail::integer_like<decltype(decay_copy(bksge::declval<U&&>().size()))>::value
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_size = typename has_member_size_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP
