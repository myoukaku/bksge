/**
 *	@file	vhea.hpp
 *
 *	@brief	VerticalHeaderTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_VHEA_HPP
#define BKSGE_CORE_FONT_OTF_VHEA_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct VerticalHeaderTable
{
	explicit VerticalHeaderTable(bksge::uint8_t const* ptr)
	{
		int16	reserved0;
		int16	reserved1;
		int16	reserved2;
		int16	reserved3;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &vertTypoAscender);
		ptr = ReadBigEndian(ptr, &vertTypoDescender);
		ptr = ReadBigEndian(ptr, &vertTypoLineGap);
		ptr = ReadBigEndian(ptr, &advanceHeightMax);
		ptr = ReadBigEndian(ptr, &minTopSideBearing);
		ptr = ReadBigEndian(ptr, &minBottomSideBearing);
		ptr = ReadBigEndian(ptr, &yMaxExtent);
		ptr = ReadBigEndian(ptr, &caretSlopeRise);
		ptr = ReadBigEndian(ptr, &caretSlopeRun);
		ptr = ReadBigEndian(ptr, &caretOffset);
		ptr = ReadBigEndian(ptr, &reserved0);
		ptr = ReadBigEndian(ptr, &reserved1);
		ptr = ReadBigEndian(ptr, &reserved2);
		ptr = ReadBigEndian(ptr, &reserved3);
		ptr = ReadBigEndian(ptr, &metricDataFormat);
		ptr = ReadBigEndian(ptr, &numOfLongVerMetrics);
	}

	Version16Dot16	version;
	int16	vertTypoAscender;
	int16	vertTypoDescender;
	int16	vertTypoLineGap;
	int16	advanceHeightMax;
	int16	minTopSideBearing;
	int16	minBottomSideBearing;
	int16	yMaxExtent;
	int16	caretSlopeRise;
	int16	caretSlopeRun;
	int16	caretOffset;
	int16	metricDataFormat;
	uint16	numOfLongVerMetrics;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_VHEA_HPP
