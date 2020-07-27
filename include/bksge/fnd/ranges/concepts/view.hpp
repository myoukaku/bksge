/**
 *	@file	view.hpp
 *
 *	@brief	view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP
#define BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/enable_view.hpp>
#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept view =
	ranges::range<T> &&
	bksge::semiregular<T> &&
	BKSGE_RANGES_ENABLE_VIEW(T);

#else

template <typename T>
using view = bksge::conjunction<
	ranges::range<T>,
	bksge::semiregular_t<T>,
	bksge::bool_constant<BKSGE_RANGES_ENABLE_VIEW(T)>
>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP
