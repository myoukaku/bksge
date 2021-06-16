/**
 *	@file	maybe_borrowed_range.hpp
 *
 *	@brief	maybe_borrowed_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP

#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept maybe_borrowed_range =
	bksge::is_lvalue_reference<T>::value ||
	BKSGE_RANGES_ENABLE_BORROWED_RANGE(bksge::remove_cvref_t<T>);

#else

template <typename T>
using maybe_borrowed_range =
	bksge::bool_constant<
		bksge::is_lvalue_reference<T>::value ||
		BKSGE_RANGES_ENABLE_BORROWED_RANGE(bksge::remove_cvref_t<T>)
	>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_DETAIL_MAYBE_BORROWED_RANGE_HPP
