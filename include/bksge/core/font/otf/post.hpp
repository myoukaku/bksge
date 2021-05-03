/**
 *	@file	post.hpp
 *
 *	@brief	PostScriptTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_POST_HPP
#define BKSGE_CORE_FONT_OTF_POST_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct PostScriptTable
{
	explicit PostScriptTable(bksge::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &italicAngle);
		ptr = ReadBigEndian(ptr, &underlinePosition);
		ptr = ReadBigEndian(ptr, &underlineThickness);
		ptr = ReadBigEndian(ptr, &isFixedPitch);
		ptr = ReadBigEndian(ptr, &minMemType42);
		ptr = ReadBigEndian(ptr, &maxMemType42);
		ptr = ReadBigEndian(ptr, &minMemType1);
		ptr = ReadBigEndian(ptr, &maxMemType1);
		if (version < 0x00020000)
		{
			return;
		}
		// Version 2.0
		uint16	numGlyphs;
		ptr = ReadBigEndian(ptr, &numGlyphs);
		glyphNameIndex.resize(numGlyphs);
		ptr = ReadBigEndian(ptr, &glyphNameIndex);

		uint8 stringLength;
		ptr = ReadBigEndian(ptr, &stringLength);
		stringData.resize(stringLength);
		ptr = ReadBigEndian(ptr, &stringData);
	}

	// Version 1.0
	Version16Dot16	version;
	Fixed			italicAngle;
	FWORD			underlinePosition;
	FWORD			underlineThickness;
	uint32			isFixedPitch;
	uint32			minMemType42;
	uint32			maxMemType42;
	uint32			minMemType1;
	uint32			maxMemType1;
	// Version 2.0
	bksge::vector<uint16>	glyphNameIndex;
	bksge::vector<uint8>	stringData;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_POST_HPP
