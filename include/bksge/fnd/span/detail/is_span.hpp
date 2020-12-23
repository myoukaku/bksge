/**
 *	@file	is_span.hpp
 *
 *	@brief	is_span の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_IS_SPAN_HPP
#define BKSGE_FND_SPAN_DETAIL_IS_SPAN_HPP

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace detail
{

// is_span
template <typename T>
struct is_span_impl
	: public bksge::false_type {};

template <typename T, bksge::size_t Extent>
struct is_span_impl<span<T, Extent>>
	: public bksge::true_type {};

template <typename T>
struct is_span
	: public is_span_impl<bksge::remove_cv_t<T>> {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_IS_SPAN_HPP
