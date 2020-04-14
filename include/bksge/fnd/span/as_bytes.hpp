/**
 *	@file	as_bytes.hpp
 *
 *	@brief	as_bytes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_AS_BYTES_HPP
#define BKSGE_FND_SPAN_AS_BYTES_HPP

#include <bksge/fnd/span/span.hpp>
#include <bksge/fnd/span/detail/as_bytes_extent.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <typename T, std::size_t Extent>
auto as_bytes(span<T, Extent> s) BKSGE_NOEXCEPT
-> span<bksge::byte const, span_detail::as_bytes_extent<T, Extent>::value>
{
	return {reinterpret_cast<bksge::byte const*>(s.data()), s.size_bytes()};
}

}	// namespace bksge

#endif // BKSGE_FND_SPAN_AS_BYTES_HPP
