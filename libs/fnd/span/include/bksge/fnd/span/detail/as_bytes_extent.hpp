/**
 *	@file	as_bytes_extent.hpp
 *
 *	@brief	as_bytes_extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DETAIL_AS_BYTES_EXTENT_HPP
#define BKSGE_FND_SPAN_DETAIL_AS_BYTES_EXTENT_HPP

#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bksge::size_t Extent>
struct as_bytes_extent
{
	static const bksge::size_t value = Extent * sizeof(T);
};

template <typename T>
struct as_bytes_extent<T, bksge::dynamic_extent>
{
	static const bksge::size_t value = bksge::dynamic_extent;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DETAIL_AS_BYTES_EXTENT_HPP
