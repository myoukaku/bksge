/**
 *	@file	not_same_as.hpp
 *
 *	@brief	not_same_as の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_NOT_SAME_AS_HPP
#define BKSGE_FND_RANGES_DETAIL_NOT_SAME_AS_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept not_same_as =
	!bksge::same_as<bksge::remove_cvref_t<T>, bksge::remove_cvref_t<U>>;

#else

template <typename T, typename U>
using not_same_as =
	bksge::negation<bksge::same_as<bksge::remove_cvref_t<T>, bksge::remove_cvref_t<U>>>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_NOT_SAME_AS_HPP
