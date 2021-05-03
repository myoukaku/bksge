/**
 *	@file	ebdt.hpp
 *
 *	@brief	EmbeddedBitmapDataTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_EBDT_HPP
#define BKSGE_CORE_FONT_OTF_EBDT_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct EmbeddedBitmapDataTable
{
	uint16	majorVersion;
	uint16	minorVersion;

	// TODO
	// BigGlyphMetrics
	// SmallGlyphMetrics
	// Glyph Bitmap Data

	explicit EmbeddedBitmapDataTable(bksge::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
	}
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_EBDT_HPP
