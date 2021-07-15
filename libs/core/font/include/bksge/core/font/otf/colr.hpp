/**
 *	@file	colr.hpp
 *
 *	@brief	ColorTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_COLR_HPP
#define BKSGE_CORE_FONT_OTF_COLR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct ColorTable
{
	struct BaseGlyphRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			BaseGlyphRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->glyphID);
			ptr = ReadBigEndian(ptr, &dst->firstLayerIndex);
			ptr = ReadBigEndian(ptr, &dst->numLayers);
			return ptr;
		}

		uint16	glyphID;
		uint16	firstLayerIndex;
		uint16	numLayers;
	};

	struct LayerRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			LayerRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->glyphID);
			ptr = ReadBigEndian(ptr, &dst->paletteIndex);
			return ptr;
		}

		uint16	glyphID;
		uint16	paletteIndex;
	};

	explicit ColorTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		version;
		uint16		numBaseGlyphRecords;
		Offset32	baseGlyphRecordsOffset;
		Offset32	layerRecordsOffset;
		uint16		numLayerRecords;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numBaseGlyphRecords);
		ptr = ReadBigEndian(ptr, &baseGlyphRecordsOffset);
		ptr = ReadBigEndian(ptr, &layerRecordsOffset);
		ptr = ReadBigEndian(ptr, &numLayerRecords);

		ptr = start + baseGlyphRecordsOffset;
		baseGlyphRecords.resize(numBaseGlyphRecords);
		ptr = ReadBigEndian(ptr, &baseGlyphRecords);

		ptr = start + layerRecordsOffset;
		layerRecords.resize(numLayerRecords);
		ptr = ReadBigEndian(ptr, &layerRecords);
	}

	bksge::vector<BaseGlyphRecord>	baseGlyphRecords;
	bksge::vector<LayerRecord>		layerRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_COLR_HPP
