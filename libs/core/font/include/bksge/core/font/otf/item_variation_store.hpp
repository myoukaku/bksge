/**
 *	@file	item_variation_store.hpp
 *
 *	@brief	ItemVariationStore の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_ITEM_VARIATION_STORE_HPP
#define BKSGE_CORE_FONT_OTF_ITEM_VARIATION_STORE_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct ItemVariationStore
{
	struct RegionAxisCoordinates
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			RegionAxisCoordinates* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->startCoord);
			ptr = ReadBigEndian(ptr, &dst->peakCoord);
			ptr = ReadBigEndian(ptr, &dst->endCoord);
			return ptr;
		}

		F2DOT14	startCoord;
		F2DOT14	peakCoord;
		F2DOT14	endCoord;
	};

	struct VariationRegion
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			VariationRegion* dst,
			uint16 axisCount)
		{
			dst->regionAxes.resize(axisCount);
			ptr = ReadBigEndian(ptr, &dst->regionAxes);
			return ptr;
		}

		bksge::vector<RegionAxisCoordinates> regionAxes;
	};

	struct VariationRegionList
	{
		explicit VariationRegionList(bksge::uint8_t const* ptr)
		{
			uint16	axisCount;
			uint16	regionCount;
			ptr = ReadBigEndian(ptr, &axisCount);
			ptr = ReadBigEndian(ptr, &regionCount);
			variationRegions.resize(regionCount);
			ptr = ReadBigEndian(ptr, &variationRegions, axisCount);
		}

		bksge::vector<VariationRegion>	variationRegions;
	};

	struct DeltaSet
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			DeltaSet* dst,
			uint16 shortDeltaCount,
			uint16 regionIndexCount)
		{
			dst->deltaData16.resize(shortDeltaCount);
			dst->deltaData8.resize(regionIndexCount - shortDeltaCount);
			ptr = ReadBigEndian(ptr, &dst->deltaData16);
			ptr = ReadBigEndian(ptr, &dst->deltaData8);
			return ptr;
		}

		bksge::vector<int16>	deltaData16;
		bksge::vector<int8>		deltaData8;
	};

	struct ItemVariationData
	{
		explicit ItemVariationData(bksge::uint8_t const* ptr)
		{
			uint16	itemCount;
			uint16	shortDeltaCount;
			uint16	regionIndexCount;

			ptr = ReadBigEndian(ptr, &itemCount);
			ptr = ReadBigEndian(ptr, &shortDeltaCount);
			ptr = ReadBigEndian(ptr, &regionIndexCount);
			regionIndexes.resize(regionIndexCount);
			ptr = ReadBigEndian(ptr, &regionIndexes);
			deltaSets.resize(itemCount);
			ptr = ReadBigEndian(ptr, &deltaSets, shortDeltaCount, regionIndexCount);
		}

		bksge::vector<uint16>	regionIndexes;
		bksge::vector<DeltaSet>	deltaSets;
	};

	explicit ItemVariationStore(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		format;
		Offset32	variationRegionListOffset;
		uint16		itemVariationDataCount;

		ptr = ReadBigEndian(ptr, &format);
		ptr = ReadBigEndian(ptr, &variationRegionListOffset);
		ptr = ReadBigEndian(ptr, &itemVariationDataCount);
		for (uint16 i = 0; i < itemVariationDataCount; ++i)
		{
			Offset32 itemVariationDataOffset;
			ptr = ReadBigEndian(ptr, &itemVariationDataOffset);
			itemVariationData.emplace_back(start + itemVariationDataOffset);
		}

		if (variationRegionListOffset != 0)
		{
			variationRegionList = bksge::make_unique<VariationRegionList>(
				start + variationRegionListOffset);
		}
	}

	bksge::unique_ptr<VariationRegionList>	variationRegionList;
	bksge::vector<ItemVariationData>		itemVariationData;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_ITEM_VARIATION_STORE_HPP
