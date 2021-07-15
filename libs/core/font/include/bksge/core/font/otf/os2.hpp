/**
 *	@file	os2.hpp
 *
 *	@brief	OS2Table の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_OS2_HPP
#define BKSGE_CORE_FONT_OTF_OS2_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct OS2Table
{
	explicit OS2Table(std::uint8_t const* ptr)
	{
		// Version 0
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &xAvgCharWidth);
		ptr = ReadBigEndian(ptr, &usWeightClass);
		ptr = ReadBigEndian(ptr, &usWidthClass);
		ptr = ReadBigEndian(ptr, &fsType);
		ptr = ReadBigEndian(ptr, &ySubscriptXSize);
		ptr = ReadBigEndian(ptr, &ySubscriptYSize);
		ptr = ReadBigEndian(ptr, &ySubscriptXOffset);
		ptr = ReadBigEndian(ptr, &ySubscriptYOffset);
		ptr = ReadBigEndian(ptr, &ySuperscriptXSize);
		ptr = ReadBigEndian(ptr, &ySuperscriptYSize);
		ptr = ReadBigEndian(ptr, &ySuperscriptXOffset);
		ptr = ReadBigEndian(ptr, &ySuperscriptYOffset);
		ptr = ReadBigEndian(ptr, &yStrikeoutSize);
		ptr = ReadBigEndian(ptr, &yStrikeoutPosition);
		ptr = ReadBigEndian(ptr, &sFamilyClass);
		ptr = ReadBigEndian(ptr, &panose);
		ptr = ReadBigEndian(ptr, &ulUnicodeRange1);
		ptr = ReadBigEndian(ptr, &ulUnicodeRange2);
		ptr = ReadBigEndian(ptr, &ulUnicodeRange3);
		ptr = ReadBigEndian(ptr, &ulUnicodeRange4);
		ptr = ReadBigEndian(ptr, &achVendID);
		ptr = ReadBigEndian(ptr, &fsSelection);
		ptr = ReadBigEndian(ptr, &usFirstCharIndex);
		ptr = ReadBigEndian(ptr, &usLastCharIndex);
		ptr = ReadBigEndian(ptr, &sTypoAscender);
		ptr = ReadBigEndian(ptr, &sTypoDescender);
		ptr = ReadBigEndian(ptr, &sTypoLineGap);
		ptr = ReadBigEndian(ptr, &usWinAscent);
		ptr = ReadBigEndian(ptr, &usWinDescent);
		if (version < 1)
		{
			return;
		}
		// Version 1
		ptr = ReadBigEndian(ptr, &ulCodePageRange1);
		ptr = ReadBigEndian(ptr, &ulCodePageRange2);
		if (version < 2)
		{
			return;
		}
		// Version 2,3,4
		ptr = ReadBigEndian(ptr, &sxHeight);
		ptr = ReadBigEndian(ptr, &sCapHeight);
		ptr = ReadBigEndian(ptr, &usDefaultChar);
		ptr = ReadBigEndian(ptr, &usBreakChar);
		ptr = ReadBigEndian(ptr, &usMaxContext);
		if (version < 5)
		{
			return; 
		}
		// Version 5
		ptr = ReadBigEndian(ptr, &usLowerOpticalPointSize);
		ptr = ReadBigEndian(ptr, &usUpperOpticalPointSize);
	}

	// Version 0
	uint16	version;
	int16	xAvgCharWidth;
	uint16	usWeightClass;
	uint16	usWidthClass;
	uint16	fsType;
	int16	ySubscriptXSize;
	int16	ySubscriptYSize;
	int16	ySubscriptXOffset;
	int16	ySubscriptYOffset;
	int16	ySuperscriptXSize;
	int16	ySuperscriptYSize;
	int16	ySuperscriptXOffset;
	int16	ySuperscriptYOffset;
	int16	yStrikeoutSize;
	int16	yStrikeoutPosition;
	int16	sFamilyClass;
	uint8	panose[10];
	uint32	ulUnicodeRange1;
	uint32	ulUnicodeRange2;
	uint32	ulUnicodeRange3;
	uint32	ulUnicodeRange4;
	Tag		achVendID;
	uint16	fsSelection;
	uint16	usFirstCharIndex;
	uint16	usLastCharIndex;
	int16	sTypoAscender;
	int16	sTypoDescender;
	int16	sTypoLineGap;
	uint16	usWinAscent;
	uint16	usWinDescent;
	// Version 1
	uint32	ulCodePageRange1 = 0;
	uint32	ulCodePageRange2 = 0;
	// Version 2,3,4
	int16	sxHeight      = 0;
	int16	sCapHeight    = 0;
	uint16	usDefaultChar = 0;
	uint16	usBreakChar   = 0;
	uint16	usMaxContext  = 0;
	// Version 5
	uint16	usLowerOpticalPointSize = 0;
	uint16	usUpperOpticalPointSize = 0;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_OS2_HPP
