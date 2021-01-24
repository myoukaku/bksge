/**
 *	@file	is_byte.hpp
 *
 *	@brief	is_byte の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_BYTE_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_BYTE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/cstddef/byte.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_byte : public bksge::false_type {};

template <>
struct is_byte<char> : public bksge::true_type {};

template <>
struct is_byte<signed char> : public bksge::true_type {};

template <>
struct is_byte<unsigned char> : public bksge::true_type {};

template <>
struct is_byte<bksge::byte> : public bksge::true_type {};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct is_byte<char8_t> : public bksge::true_type {};
#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_BYTE_HPP
