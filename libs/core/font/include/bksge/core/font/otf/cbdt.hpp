/**
 *	@file	cbdt.hpp
 *
 *	@brief	ColorBitmapDataTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CBDT_HPP
#define BKSGE_CORE_FONT_OTF_CBDT_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct ColorBitmapDataTable
{
	uint16	majorVersion;
	uint16	minorVersion;
	// TODO
	// Uncompressed Color Bitmaps
	// Compressed Color Bitmaps
	// Glyph Metrics

	explicit ColorBitmapDataTable(std::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
	}
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CBDT_HPP
