/**
 *	@file	cpal.hpp
 *
 *	@brief	ColorPaletteTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CPAL_HPP
#define BKSGE_CORE_FONT_OTF_CPAL_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct ColorPaletteTable
{
	struct ColorRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, ColorRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->blue);
			ptr = ReadBigEndian(ptr, &dst->green);
			ptr = ReadBigEndian(ptr, &dst->red);
			ptr = ReadBigEndian(ptr, &dst->alpha);
			return ptr;
		}

		uint8	blue;
		uint8	green;
		uint8	red;
		uint8	alpha;
	};

	explicit ColorPaletteTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		version;
		uint16		numPaletteEntries;
		uint16		numPalettes;
		uint16		numColorRecords;
		Offset32	colorRecordsArrayOffset;
		Offset32	paletteTypesArrayOffset = 0;		// version 1
		Offset32	paletteLabelsArrayOffset = 0;		// version 1
		Offset32	paletteEntryLabelsArrayOffset = 0;	// version 1

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numPaletteEntries);
		ptr = ReadBigEndian(ptr, &numPalettes);
		ptr = ReadBigEndian(ptr, &numColorRecords);
		ptr = ReadBigEndian(ptr, &colorRecordsArrayOffset);
		colorRecordIndices.resize(numPalettes);
		ptr = ReadBigEndian(ptr, &colorRecordIndices);

		if (version == 1)
		{
			ptr = ReadBigEndian(ptr, &paletteTypesArrayOffset);
			ptr = ReadBigEndian(ptr, &paletteLabelsArrayOffset);
			ptr = ReadBigEndian(ptr, &paletteEntryLabelsArrayOffset);
		}

		ptr = start + colorRecordsArrayOffset;
		colorRecords.resize(numColorRecords);
		ptr = ReadBigEndian(ptr, &colorRecords);

		if (paletteTypesArrayOffset != 0)
		{
			ptr = start + paletteTypesArrayOffset;
			paletteTypes.resize(numPalettes);
			ptr = ReadBigEndian(ptr, &paletteTypes);
		}

		if (paletteLabelsArrayOffset != 0)
		{
			ptr = start + paletteLabelsArrayOffset;
			paletteLabels.resize(numPalettes);
			ptr = ReadBigEndian(ptr, &paletteLabels);
		}

		if (paletteEntryLabelsArrayOffset != 0)
		{
			ptr = start + paletteEntryLabelsArrayOffset;
			paletteEntryLabels.resize(numPaletteEntries);
			ptr = ReadBigEndian(ptr, &paletteEntryLabels);
		}
	}

	bksge::vector<uint16>		colorRecordIndices;
	bksge::vector<ColorRecord>	colorRecords;
	bksge::vector<uint32>		paletteTypes;
	bksge::vector<uint16>		paletteLabels;
	bksge::vector<uint16>		paletteEntryLabels;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CPAL_HPP
