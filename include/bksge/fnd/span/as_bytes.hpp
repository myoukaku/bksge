/**
 *	@file	as_bytes.hpp
 *
 *	@brief	as_bytes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_AS_BYTES_HPP
#define BKSGE_FND_SPAN_AS_BYTES_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002) && \
	defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

namespace bksge
{

using std::as_bytes;

}	// namespace bksge

#else

#include <bksge/fnd/span/span.hpp>
#include <bksge/fnd/span/detail/as_bytes_extent.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <cstddef>

namespace bksge
{

template <typename T, std::size_t Extent>
inline span<bksge::byte const, detail::as_bytes_extent<T, Extent>::value>
as_bytes(span<T, Extent> s) BKSGE_NOEXCEPT
{
	return span<bksge::byte const, detail::as_bytes_extent<T, Extent>::value>
	{
		reinterpret_cast<bksge::byte const*>(s.data()), s.size_bytes()
	};
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_SPAN_AS_BYTES_HPP
