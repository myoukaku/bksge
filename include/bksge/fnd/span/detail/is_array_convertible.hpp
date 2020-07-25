/**
 *	@file	is_array_convertible.hpp
 *
 *	@brief	is_array_convertible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_IS_ARRAY_CONVERTIBLE_HPP
#define BKSGE_FND_SPAN_DETAIL_IS_ARRAY_CONVERTIBLE_HPP

#include <bksge/fnd/type_traits/is_convertible.hpp>

namespace bksge
{

namespace detail
{

template <typename ToElementType, typename FromElementType>
using is_array_convertible =
	bksge::is_convertible<FromElementType(*)[], ToElementType(*)[]>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_IS_ARRAY_CONVERTIBLE_HPP
