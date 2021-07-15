/**
 *	@file	hhea.hpp
 *
 *	@brief	HorizontalHeaderTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_HHEA_HPP
#define BKSGE_CORE_FONT_OTF_HHEA_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct HorizontalHeaderTable
{
	explicit HorizontalHeaderTable(std::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &ascender);
		ptr = ReadBigEndian(ptr, &descender);
		ptr = ReadBigEndian(ptr, &lineGap);
		ptr = ReadBigEndian(ptr, &advanceWidthMax);
		ptr = ReadBigEndian(ptr, &minLeftSideBearing);
		ptr = ReadBigEndian(ptr, &minRightSideBearing);
		ptr = ReadBigEndian(ptr, &xMaxExtent);
		ptr = ReadBigEndian(ptr, &caretSlopeRise);
		ptr = ReadBigEndian(ptr, &caretSlopeRun);
		ptr = ReadBigEndian(ptr, &caretOffset);
		ptr = ReadBigEndian(ptr, &reserved0);
		ptr = ReadBigEndian(ptr, &reserved1);
		ptr = ReadBigEndian(ptr, &reserved2);
		ptr = ReadBigEndian(ptr, &reserved3);
		ptr = ReadBigEndian(ptr, &metricDataFormat);
		ptr = ReadBigEndian(ptr, &numberOfHMetrics);
	}

	uint16	majorVersion;
	uint16	minorVersion;
	FWORD	ascender;
	FWORD	descender;
	FWORD	lineGap;
	UFWORD	advanceWidthMax;
	FWORD	minLeftSideBearing;
	FWORD	minRightSideBearing;
	FWORD	xMaxExtent;
	int16	caretSlopeRise;
	int16	caretSlopeRun;
	int16	caretOffset;
	int16	reserved0;
	int16	reserved1;
	int16	reserved2;
	int16	reserved3;
	int16	metricDataFormat;
	uint16	numberOfHMetrics;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_HHEA_HPP
