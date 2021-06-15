/**
 *	@file	is_span_compatible_ref.hpp
 *
 *	@brief	is_span_compatible_ref の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_REF_HPP
#define BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_REF_HPP

#include <bksge/fnd/span/detail/is_array_convertible.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>

namespace bksge
{

namespace detail
{

template <typename T, typename Ref>
using is_span_compatible_ref =
	detail::is_array_convertible<T, bksge::remove_reference_t<Ref>>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_IS_SPAN_COMPATIBLE_REF_HPP
