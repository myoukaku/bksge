/**
 *	@file	hvar.hpp
 *
 *	@brief	HorizontalMetricsVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_HVAR_HPP
#define BKSGE_CORE_FONT_OTF_HVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/item_variation_store.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct HorizontalMetricsVariationsTable
{
	enum EntryFormat
	{
		INNER_INDEX_BIT_COUNT_MASK = 0x000F,
		MAP_ENTRY_SIZE_MASK = 0x0030,
	};

	struct DeltaSetIndexMap
	{
		explicit DeltaSetIndexMap(bksge::uint8_t const* ptr)
		{
			ptr = ReadBigEndian(ptr, &entryFormat);
			ptr = ReadBigEndian(ptr, &mapCount);
			mapData.resize(mapCount);
			ptr = ReadBigEndian(ptr, &mapData);
		}

		uint16					entryFormat;
		uint16					mapCount;
		bksge::vector<uint8>	mapData;
	};

	explicit HorizontalMetricsVariationsTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset32	itemVariationStoreOffset;
		Offset32	advanceWidthMappingOffset;
		Offset32	lsbMappingOffset;
		Offset32	rsbMappingOffset;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &itemVariationStoreOffset);
		ptr = ReadBigEndian(ptr, &advanceWidthMappingOffset);
		ptr = ReadBigEndian(ptr, &lsbMappingOffset);
		ptr = ReadBigEndian(ptr, &rsbMappingOffset);

		if (itemVariationStoreOffset != 0)
		{
			itemVariationStore = bksge::make_unique<ItemVariationStore>(
				start + itemVariationStoreOffset);
		}
		if (advanceWidthMappingOffset != 0)
		{
			advanceWidthMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + advanceWidthMappingOffset);
		}
		if (lsbMappingOffset != 0)
		{
			lsbMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + lsbMappingOffset);
		}
		if (rsbMappingOffset != 0)
		{
			rsbMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + rsbMappingOffset);
		}
	}

	bksge::unique_ptr<ItemVariationStore>	itemVariationStore;
	bksge::unique_ptr<DeltaSetIndexMap>		advanceWidthMapping;
	bksge::unique_ptr<DeltaSetIndexMap>		lsbMapping;
	bksge::unique_ptr<DeltaSetIndexMap>		rsbMapping;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_HVAR_HPP
