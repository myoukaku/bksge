/**
 *	@file	base.hpp
 *
 *	@brief	BaselineTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_BASE_HPP
#define BKSGE_CORE_FONT_OTF_BASE_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/item_variation_store.hpp>
#include <bksge/core/font/otf/device_table.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct BaselineTable
{
	struct BaseCoord
	{
		explicit BaseCoord(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16 deviceOffset = 0;		// Format 3

			ptr = ReadBigEndian(ptr, &baseCoordFormat);
			ptr = ReadBigEndian(ptr, &coordinate);
			if (baseCoordFormat == 2)
			{
				ptr = ReadBigEndian(ptr, &referenceGlyph);
				ptr = ReadBigEndian(ptr, &baseCoordPoint);
			}
			if (baseCoordFormat == 3)
			{
				ptr = ReadBigEndian(ptr, &deviceOffset);
			}

			if (deviceOffset != 0)
			{
				device = bksge::make_unique<DeviceTable>(
					start + deviceOffset);
			}
		}

		uint16		baseCoordFormat;
		int16		coordinate;
		uint16		referenceGlyph = 0;			// Format 2
		uint16		baseCoordPoint = 0;			// Format 2
		bksge::unique_ptr<DeviceTable>	device;	// Format 3
	};

	struct FeatMinMaxRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			FeatMinMaxRecord* dst,
			std::uint8_t const* start)
		{
			Offset16	minCoordOffset;
			Offset16	maxCoordOffset;

			ptr = ReadBigEndian(ptr, &dst->featureTableTag);
			ptr = ReadBigEndian(ptr, &minCoordOffset);
			ptr = ReadBigEndian(ptr, &maxCoordOffset);
			if (minCoordOffset != 0)
			{
				dst->minCoord = bksge::make_unique<BaseCoord>(
					start + minCoordOffset);
			}
			if (maxCoordOffset != 0)
			{
				dst->maxCoord = bksge::make_unique<BaseCoord>(
					start + maxCoordOffset);
			}
			return ptr;
		}

		Tag								featureTableTag;
		bksge::unique_ptr<BaseCoord>	minCoord;
		bksge::unique_ptr<BaseCoord>	maxCoord;
	};

	struct MinMax
	{
		explicit MinMax(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	minCoordOffset;
			Offset16	maxCoordOffset;
			uint16		featMinMaxCount;

			ptr = ReadBigEndian(ptr, &minCoordOffset);
			ptr = ReadBigEndian(ptr, &maxCoordOffset);
			ptr = ReadBigEndian(ptr, &featMinMaxCount);
			featMinMaxRecords.resize(featMinMaxCount);
			ptr = ReadBigEndian(ptr, &featMinMaxRecords, start);

			if (minCoordOffset != 0)
			{
				minCoord = bksge::make_unique<BaseCoord>(
					start + minCoordOffset);
			}
			if (maxCoordOffset != 0)
			{
				maxCoord = bksge::make_unique<BaseCoord>(
					start + maxCoordOffset);
			}
		}

		bksge::unique_ptr<BaseCoord>	minCoord;
		bksge::unique_ptr<BaseCoord>	maxCoord;
		bksge::vector<FeatMinMaxRecord>	featMinMaxRecords;
	};

	struct BaseValues
	{
		explicit BaseValues(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	baseCoordCount;
			ptr = ReadBigEndian(ptr, &defaultBaselineIndex);
			ptr = ReadBigEndian(ptr, &baseCoordCount);
			for (uint16 i = 0; i < baseCoordCount; ++i)
			{
				Offset16 baseCoordOffset;
				ptr = ReadBigEndian(ptr, &baseCoordOffset);
				baseCoord.emplace_back(start + baseCoordOffset);
			}
		}

		uint16						defaultBaselineIndex;
		bksge::vector<BaseCoord>	baseCoord;
	};

	struct BaseLangSysRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			BaseLangSysRecord* dst,
			std::uint8_t const* start)
		{
			Offset16 minMaxOffset;
			ptr = ReadBigEndian(ptr, &dst->baseLangSysTag);
			ptr = ReadBigEndian(ptr, &minMaxOffset);

			dst->minMax = bksge::make_unique<MinMax>(
				start + minMaxOffset);
			return ptr;
		}

		Tag							baseLangSysTag;
		bksge::unique_ptr<MinMax>	minMax;
	};

	struct BaseScript
	{
		explicit BaseScript(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	baseValuesOffset;
			Offset16	defaultMinMaxOffset;
			uint16		baseLangSysCount;

			ptr = ReadBigEndian(ptr, &baseValuesOffset);
			ptr = ReadBigEndian(ptr, &defaultMinMaxOffset);
			ptr = ReadBigEndian(ptr, &baseLangSysCount);
			baseLangSysRecords.resize(baseLangSysCount);
			ptr = ReadBigEndian(ptr, &baseLangSysRecords, start);

			if (baseValuesOffset != 0)
			{
				baseValues = bksge::make_unique<BaseValues>(
					start + baseValuesOffset);
			}
			if (defaultMinMaxOffset != 0)
			{
				defaultMinMax = bksge::make_unique<MinMax>(
					start + defaultMinMaxOffset);
			}
		}

		bksge::unique_ptr<BaseValues>		baseValues;
		bksge::unique_ptr<MinMax>			defaultMinMax;
		bksge::vector<BaseLangSysRecord>	baseLangSysRecords;
	};

	struct BaseScriptRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			BaseScriptRecord* dst,
			std::uint8_t const* start)
		{
			Offset16 baseScriptOffset;

			ptr = ReadBigEndian(ptr, &dst->baseScriptTag);
			ptr = ReadBigEndian(ptr, &baseScriptOffset);

			dst->baseScript = bksge::make_unique<BaseScript>(
				start + baseScriptOffset);
			return ptr;
		}

		Tag								baseScriptTag;
		bksge::unique_ptr<BaseScript>	baseScript;
	};

	struct BaseScriptList
	{
		explicit BaseScriptList(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	baseScriptCount;
			ptr = ReadBigEndian(ptr, &baseScriptCount);

			baseScriptRecords.resize(baseScriptCount);
			ptr = ReadBigEndian(ptr, &baseScriptRecords, start);
		}

		bksge::vector<BaseScriptRecord>	baseScriptRecords;
	};

	struct BaseTagList
	{
		explicit BaseTagList(std::uint8_t const* ptr)
		{
			uint16	baseTagCount;
			ptr = ReadBigEndian(ptr, &baseTagCount);
			baselineTags.resize(baseTagCount);
			ptr = ReadBigEndian(ptr, &baselineTags);
		}

		bksge::vector<Tag>	baselineTags;
	};

	struct Axis
	{
		explicit Axis(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	baseTagListOffset;
			Offset16	baseScriptListOffset;
			ptr = ReadBigEndian(ptr, &baseTagListOffset);
			ptr = ReadBigEndian(ptr, &baseScriptListOffset);

			// BaseTagList Table
			if (baseTagListOffset != 0)
			{
				baseTagList = bksge::make_unique<BaseTagList>(
					start + baseTagListOffset);
			}

			// BaseScriptList Table
			if (baseScriptListOffset != 0)
			{
				baseScriptList = bksge::make_unique<BaseScriptList>(
					start + baseScriptListOffset);
			}
		}

		bksge::unique_ptr<BaseTagList>		baseTagList;
		bksge::unique_ptr<BaseScriptList>	baseScriptList;
	};

	explicit BaselineTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;

		// BASE Header, Version 1.0
		Offset16	horizAxisOffset    = 0;
		Offset16	vertAxisOffset     = 0;
		// BASE Header, Version 1.1
		Offset32	itemVarStoreOffset = 0;

		// Header
		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &horizAxisOffset);
		ptr = ReadBigEndian(ptr, &vertAxisOffset);
		if (majorVersion == 1 &&
			minorVersion == 1)
		{
			// Version 1.1
			ptr = ReadBigEndian(ptr, &itemVarStoreOffset);
		}

		if (horizAxisOffset != 0)
		{
			horizAxis = bksge::make_unique<Axis>(
				start + horizAxisOffset);
		}

		if (vertAxisOffset != 0)
		{
			vertAxis = bksge::make_unique<Axis>(
				start + vertAxisOffset);
		}

		if (itemVarStoreOffset != 0)
		{
			itemVarStore = bksge::make_unique<ItemVariationStore>(
				start + itemVarStoreOffset);
		}
	}

	bksge::unique_ptr<Axis>					horizAxis;
	bksge::unique_ptr<Axis>					vertAxis;
	bksge::unique_ptr<ItemVariationStore>	itemVarStore;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_BASE_HPP
