﻿/**
 *	@file	as_writable_bytes.hpp
 *
 *	@brief	as_writable_bytes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP
#define BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP

#include <bksge/fnd/span/config.hpp>

#if defined(BKSGE_USE_STD_SPAN)

namespace bksge
{

using std::as_writable_bytes;

}	// namespace bksge

#else

#include <bksge/fnd/span/span.hpp>
#include <bksge/fnd/span/detail/as_bytes_extent.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <cstddef>

namespace bksge
{

template <typename T, std::size_t Extent>
inline span<bksge::byte, detail::as_bytes_extent<T, Extent>::value>
as_writable_bytes(span<T, Extent> s) BKSGE_NOEXCEPT
{
	return span<bksge::byte, detail::as_bytes_extent<T, Extent>::value>
	{
		reinterpret_cast<bksge::byte*>(s.data()), s.size_bytes()
	};
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP
