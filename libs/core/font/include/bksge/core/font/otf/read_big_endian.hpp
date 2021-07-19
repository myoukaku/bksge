/**
 *	@file	read_big_endian.hpp
 *
 *	@brief	ReadBigEndian 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_READ_BIG_ENDIAN_HPP
#define BKSGE_CORE_FONT_OTF_READ_BIG_ENDIAN_HPP

#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace bksge
{

namespace otf
{

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::int64_t* dst)
{
	std::uint64_t a = *src++;
	std::uint64_t b = *src++;
	std::uint64_t c = *src++;
	std::uint64_t d = *src++;
	std::uint64_t e = *src++;
	std::uint64_t f = *src++;
	std::uint64_t g = *src++;
	std::uint64_t h = *src++;
	*dst = static_cast<std::int64_t>(
		(a << 56) |
		(b << 48) |
		(c << 40) |
		(d << 32) |
		(e << 24) |
		(f << 16) |
		(g << 8) |
		h);
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::uint32_t* dst)
{
	std::uint32_t a = *src++;
	std::uint32_t b = *src++;
	std::uint32_t c = *src++;
	std::uint32_t d = *src++;
	*dst = (a << 24) | (b << 16) | (c << 8) | d;
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::int32_t* dst)
{
	std::uint32_t a = *src++;
	std::uint32_t b = *src++;
	std::uint32_t c = *src++;
	std::uint32_t d = *src++;
	*dst = static_cast<std::int32_t>(
		(a << 24) | (b << 16) | (c << 8) | d);
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::uint16_t* dst)
{
	std::uint16_t a = *src++;
	std::uint16_t b = *src++;
	*dst = (a << 8) | b;
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::int16_t* dst)
{
	std::uint16_t a = *src++;
	std::uint16_t b = *src++;
	*dst = static_cast<std::int16_t>(
		(a << 8) | b);
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::uint8_t* dst)
{
	*dst = *src++;
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::int8_t* dst)
{
	*dst = static_cast<std::int8_t>(*src++);
	return src;
}

template <std::size_t N>
inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::uint8_t (*dst)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		(*dst)[i] = *src++;
	}
	return src;
}

template <std::size_t N>
inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, std::uint16_t (*dst)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		std::uint16_t a = *src++;
		std::uint16_t b = *src++;
		(*dst)[i] = (a << 8) | b;
	}
	return src;
}

inline
std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, uint24* dst)
{
	return ReadBigEndian(src, &dst->value);
}


template <typename T, typename... Args>
inline std::uint8_t const* ReadBigEndian(
	std::uint8_t const* src, bksge::vector<T>* dst, Args&&... args)
{
	for (auto& x : *dst)
	{
		src = ReadBigEndian(src, &x, std::forward<Args>(args)...);
	}
	return src;
}

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_READ_BIG_ENDIAN_HPP
