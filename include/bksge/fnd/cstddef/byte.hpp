/**
 *	@file	byte.hpp
 *
 *	@brief	byte の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CSTDDEF_BYTE_HPP
#define BKSGE_FND_CSTDDEF_BYTE_HPP

#include <cstddef>

#if defined(__cpp_lib_byte) && (__cpp_lib_byte >= 201603)

namespace bksge
{

using std::byte;
using std::to_integer;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

enum class byte : unsigned char {};

template <typename IntegerType>
inline BKSGE_CONSTEXPR bksge::enable_if_t<bksge::is_integral<IntegerType>::value, IntegerType>
to_integer(byte b) BKSGE_NOEXCEPT
{
	return IntegerType(b);
}

inline BKSGE_CONSTEXPR byte operator|(byte lhs, byte rhs) BKSGE_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
}

inline BKSGE_CONSTEXPR byte operator&(byte lhs, byte rhs) BKSGE_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
}

inline BKSGE_CONSTEXPR byte operator^(byte lhs, byte rhs) BKSGE_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
}

inline BKSGE_CONSTEXPR byte operator~(byte b) BKSGE_NOEXCEPT
{
	return byte(~static_cast<unsigned char>(b));
}

inline BKSGE_CXX14_CONSTEXPR byte& operator|=(byte& lhs, byte rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs | rhs;
}

inline BKSGE_CXX14_CONSTEXPR byte& operator&=(byte& lhs, byte rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs & rhs;
}

inline BKSGE_CXX14_CONSTEXPR byte& operator^=(byte& lhs, byte rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs ^ rhs;
}

template <typename IntegerType>
inline BKSGE_CONSTEXPR bksge::enable_if_t<bksge::is_integral<IntegerType>::value, byte>
operator<<(byte lhs, IntegerType shift) BKSGE_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) << shift);
}

template <typename IntegerType>
inline BKSGE_CONSTEXPR bksge::enable_if_t<bksge::is_integral<IntegerType>::value, byte>
operator>>(byte lhs, IntegerType shift) BKSGE_NOEXCEPT
{
	return byte(static_cast<unsigned char>(lhs) >> shift);
}

template <typename IntegerType>
inline BKSGE_CXX14_CONSTEXPR bksge::enable_if_t<bksge::is_integral<IntegerType>::value, byte>&
operator<<=(byte& lhs, IntegerType shift) BKSGE_NOEXCEPT
{
	return lhs = lhs << shift;
}

template <typename IntegerType>
inline BKSGE_CXX14_CONSTEXPR bksge::enable_if_t<bksge::is_integral<IntegerType>::value, byte>&
operator>>=(byte& lhs, IntegerType shift) BKSGE_NOEXCEPT
{
	return lhs = lhs >> shift;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_CSTDDEF_BYTE_HPP
