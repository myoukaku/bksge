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
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <cstddef>

namespace bksge
{

namespace otf
{

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::int64_t* dst)
{
	bksge::uint64_t a = *src++;
	bksge::uint64_t b = *src++;
	bksge::uint64_t c = *src++;
	bksge::uint64_t d = *src++;
	bksge::uint64_t e = *src++;
	bksge::uint64_t f = *src++;
	bksge::uint64_t g = *src++;
	bksge::uint64_t h = *src++;
	*dst = static_cast<bksge::int64_t>(
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
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::uint32_t* dst)
{
	bksge::uint32_t a = *src++;
	bksge::uint32_t b = *src++;
	bksge::uint32_t c = *src++;
	bksge::uint32_t d = *src++;
	*dst = (a << 24) | (b << 16) | (c << 8) | d;
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::int32_t* dst)
{
	bksge::uint32_t a = *src++;
	bksge::uint32_t b = *src++;
	bksge::uint32_t c = *src++;
	bksge::uint32_t d = *src++;
	*dst = static_cast<bksge::int32_t>(
		(a << 24) | (b << 16) | (c << 8) | d);
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::uint16_t* dst)
{
	bksge::uint16_t a = *src++;
	bksge::uint16_t b = *src++;
	*dst = (a << 8) | b;
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::int16_t* dst)
{
	bksge::uint16_t a = *src++;
	bksge::uint16_t b = *src++;
	*dst = static_cast<bksge::int16_t>(
		(a << 8) | b);
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::uint8_t* dst)
{
	*dst = *src++;
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::int8_t* dst)
{
	*dst = static_cast<bksge::int8_t>(*src++);
	return src;
}

template <std::size_t N>
inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::uint8_t (*dst)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		(*dst)[i] = *src++;
	}
	return src;
}

template <std::size_t N>
inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::uint16_t (*dst)[N])
{
	for (std::size_t i = 0; i < N; ++i)
	{
		bksge::uint16_t a = *src++;
		bksge::uint16_t b = *src++;
		(*dst)[i] = (a << 8) | b;
	}
	return src;
}

inline
bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, uint24* dst)
{
	return ReadBigEndian(src, &dst->value);
}


template <typename T, typename... Args>
inline bksge::uint8_t const* ReadBigEndian(
	bksge::uint8_t const* src, bksge::vector<T>* dst, Args&&... args)
{
	for (auto& x : *dst)
	{
		src = ReadBigEndian(src, &x, bksge::forward<Args>(args)...);
	}
	return src;
}

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_READ_BIG_ENDIAN_HPP
