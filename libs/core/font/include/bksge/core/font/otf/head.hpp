/**
 *	@file	head.hpp
 *
 *	@brief	FontHeaderTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_HEAD_HPP
#define BKSGE_CORE_FONT_OTF_HEAD_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct FontHeaderTable
{
	explicit FontHeaderTable(bksge::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &fontRevision);
		ptr = ReadBigEndian(ptr, &checksumAdjustment);
		ptr = ReadBigEndian(ptr, &magicNumber);
		ptr = ReadBigEndian(ptr, &flags);
		ptr = ReadBigEndian(ptr, &unitsPerEm);
		ptr = ReadBigEndian(ptr, &created);
		ptr = ReadBigEndian(ptr, &modified);
		ptr = ReadBigEndian(ptr, &xMin);
		ptr = ReadBigEndian(ptr, &yMin);
		ptr = ReadBigEndian(ptr, &xMax);
		ptr = ReadBigEndian(ptr, &yMax);
		ptr = ReadBigEndian(ptr, &macStyle);
		ptr = ReadBigEndian(ptr, &lowestRecPPEM);
		ptr = ReadBigEndian(ptr, &fontDirectionHint);
		ptr = ReadBigEndian(ptr, &indexToLocFormat);
		ptr = ReadBigEndian(ptr, &glyphDataFormat);
	}

	uint16			majorVersion;
	uint16			minorVersion;
	Fixed			fontRevision;
	uint32			checksumAdjustment;
	uint32			magicNumber;
	uint16			flags;
	uint16			unitsPerEm;
	LONGDATETIME	created;
	LONGDATETIME	modified;
	int16			xMin;
	int16			yMin;
	int16			xMax;
	int16			yMax;
	uint16			macStyle;
	uint16			lowestRecPPEM;
	int16			fontDirectionHint;
	int16			indexToLocFormat;
	int16			glyphDataFormat;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_HEAD_HPP
