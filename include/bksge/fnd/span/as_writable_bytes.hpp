/**
 *	@file	as_writable_bytes.hpp
 *
 *	@brief	as_writable_bytes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP
#define BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP

#include <bksge/fnd/span/span.hpp>
#include <bksge/fnd/span/detail/as_bytes_extent.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <
	typename T, std::size_t Extent,
	typename = bksge::enable_if_t<!bksge::is_const<T>::value>
>
auto as_writable_bytes(span<T, Extent> s) BKSGE_NOEXCEPT
-> span<bksge::byte, span_detail::as_bytes_extent<T, Extent>::value>
{
	return {reinterpret_cast<bksge::byte*>(s.data()), s.size_bytes()};
}

}	// namespace bksge

#endif // BKSGE_FND_SPAN_AS_WRITABLE_BYTES_HPP
