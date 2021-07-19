/**
 *	@file	tuple_cat.hpp
 *
 *	@brief	tuple_cat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_CAT_HPP
#define BKSGE_FND_TUPLE_TUPLE_CAT_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::tuple_cat;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/detail/tuple_concater.hpp>
#include <bksge/fnd/tuple/detail/tuple_cat_result.hpp>
#include <bksge/fnd/tuple/detail/is_tuple_like.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <typename... Tuples,
	typename = bksge::enable_if_t<bksge::conjunction<
		tuple_detail::is_tuple_like<Tuples>...
	>::value>>
inline BKSGE_CONSTEXPR auto
tuple_cat(Tuples&&... args)
-> tuple_detail::tuple_cat_result_t<Tuples...>
{
	using ret = tuple_detail::tuple_cat_result_t<Tuples...>;
	using concater = tuple_detail::tuple_concater<ret, Tuples...>;
	return concater::invoke(std::forward<Tuples>(args)...);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_TUPLE_TUPLE_CAT_HPP
