/**
 *	@file	sbix.hpp
 *
 *	@brief	StandardBitmapGraphicsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_SBIX_HPP
#define BKSGE_CORE_FONT_OTF_SBIX_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct StandardBitmapGraphicsTable
{
	explicit StandardBitmapGraphicsTable(bksge::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &flags);
		ptr = ReadBigEndian(ptr, &numStrikes);
		strikeOffsets.resize(numStrikes);
		ptr = ReadBigEndian(ptr, &strikeOffsets);
	}

	uint16	version;
	uint16	flags;
	uint32	numStrikes;
	bksge::vector<Offset32>	strikeOffsets;
	// TODO
	// Strikes
	// Glyph data
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_SBIX_HPP
