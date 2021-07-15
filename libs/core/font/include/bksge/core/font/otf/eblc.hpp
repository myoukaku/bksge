/**
 *	@file	eblc.hpp
 *
 *	@brief	EmbeddedBitmapLocationTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_EBLC_HPP
#define BKSGE_CORE_FONT_OTF_EBLC_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct EmbeddedBitmapLocationTable
{
	struct SbitLineMetrics
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, SbitLineMetrics* dst)
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

	struct BitmapSize
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, BitmapSize* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->indexSubTableArrayOffset);
			ptr = ReadBigEndian(ptr, &dst->indexTablesSize);
			ptr = ReadBigEndian(ptr, &dst->numberOfIndexSubTables);
			ptr = ReadBigEndian(ptr, &dst->colorRef);
			ptr = ReadBigEndian(ptr, &dst->hori);
			ptr = ReadBigEndian(ptr, &dst->vert);
			ptr = ReadBigEndian(ptr, &dst->startGlyphIndex);
			ptr = ReadBigEndian(ptr, &dst->endGlyphIndex);
			ptr = ReadBigEndian(ptr, &dst->ppemX);
			ptr = ReadBigEndian(ptr, &dst->ppemY);
			ptr = ReadBigEndian(ptr, &dst->bitDepth);
			ptr = ReadBigEndian(ptr, &dst->flags);

			// TODO indexSubTableArray

			return ptr;
		}

		Offset32		indexSubTableArrayOffset;
		uint32			indexTablesSize;
		uint32			numberOfIndexSubTables;
		uint32			colorRef;
		SbitLineMetrics	hori;
		SbitLineMetrics	vert;
		uint16			startGlyphIndex;
		uint16			endGlyphIndex;
		uint8			ppemX;
		uint8			ppemY;
		uint8			bitDepth;
		int8			flags;
	};

	explicit EmbeddedBitmapLocationTable(std::uint8_t const* ptr)
	{
		uint16	majorVersion;
		uint16	minorVersion;
		uint32	numSizes;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &numSizes);
		bitmapSizes.resize(numSizes);
		ptr = ReadBigEndian(ptr, &bitmapSizes);
	}

	bksge::vector<BitmapSize>	bitmapSizes;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_EBLC_HPP
