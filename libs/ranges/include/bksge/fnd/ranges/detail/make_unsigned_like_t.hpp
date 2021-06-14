/**
 *	@file	make_unsigned_like_t.hpp
 *
 *	@brief	make_unsigned_like_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP
#define BKSGE_FND_RANGES_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP

#include <bksge/fnd/ranges/detail/max_diff_type.hpp>
#include <bksge/fnd/ranges/detail/max_size_type.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename T, bool MaxDiff = bksge::is_same<T, detail::max_diff_type>::value>
using make_unsigned_like_t =
	bksge::conditional_t<MaxDiff, detail::max_size_type, bksge::make_unsigned_t<T>>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP
