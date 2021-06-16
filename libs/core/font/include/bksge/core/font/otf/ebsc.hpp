/**
 *	@file	ebsc.hpp
 *
 *	@brief	EmbeddedBitmapScalingTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_EBSC_HPP
#define BKSGE_CORE_FONT_OTF_EBSC_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct EmbeddedBitmapScalingTable
{
	struct SbitLineMetrics
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, SbitLineMetrics* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->ascender);
			ptr = ReadBigEndian(ptr, &dst->descender);
			ptr = ReadBigEndian(ptr, &dst->widthMax);
			ptr = ReadBigEndian(ptr, &dst->caretSlopeNumerator);
			ptr = ReadBigEndian(ptr, &dst->caretSlopeDenominator);
			ptr = ReadBigEndian(ptr, &dst->caretOffset);
			ptr = ReadBigEndian(ptr, &dst->minOriginSB);
			ptr = ReadBigEndian(ptr, &dst->minAdvanceSB);
			ptr = ReadBigEndian(ptr, &dst->maxBeforeBL);
			ptr = ReadBigEndian(ptr, &dst->minAfterBL);
			ptr = ReadBigEndian(ptr, &dst->pad1);
			ptr = ReadBigEndian(ptr, &dst->pad2);
			return ptr;
		}

		int8	ascender;
		int8	descender;
		uint8	widthMax;
		int8	caretSlopeNumerator;
		int8	caretSlopeDenominator;
		int8	caretOffset;
		int8	minOriginSB;
		int8	minAdvanceSB;
		int8	maxBeforeBL;
		int8	minAfterBL;
		int8	pad1;
		int8	pad2;
	};

	struct BitmapScale
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, BitmapScale* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->hori);
			ptr = ReadBigEndian(ptr, &dst->vert);
			ptr = ReadBigEndian(ptr, &dst->ppemX);
			ptr = ReadBigEndian(ptr, &dst->ppemY);
			ptr = ReadBigEndian(ptr, &dst->substitutePpemX);
			ptr = ReadBigEndian(ptr, &dst->substitutePpemY);
			return ptr;
		}

		SbitLineMetrics	hori;
		SbitLineMetrics	vert;
		uint8			ppemX;
		uint8			ppemY;
		uint8			substitutePpemX;
		uint8			substitutePpemY;
	};

	explicit EmbeddedBitmapScalingTable(bksge::uint8_t const* ptr)
	{
		uint16	majorVersion;
		uint16	minorVersion;
		uint32	numSizes;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &numSizes);
		bitmapScales.resize(numSizes);
		ptr = ReadBigEndian(ptr, &bitmapScales);
	}

	bksge::vector<BitmapScale>	bitmapScales;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_EBSC_HPP
