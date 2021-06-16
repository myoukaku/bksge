/**
 *	@file	gpos.hpp
 *
 *	@brief	GlyphPositioningTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GPOS_HPP
#define BKSGE_CORE_FONT_OTF_GPOS_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/script_list.hpp>
#include <bksge/core/font/otf/feature_list.hpp>
#include <bksge/core/font/otf/lookup_list.hpp>
#include <bksge/core/font/otf/feature_variations.hpp>
#include <bksge/core/font/otf/coverage_table.hpp>
#include <bksge/core/font/otf/class_definition_table.hpp>
#include <bksge/core/font/otf/device_table.hpp>
#include <bksge/core/font/otf/sequence_context.hpp>
#include <bksge/core/font/otf/chained_sequence_context.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct GlyphPositioningTable
{
	struct ValueRecord
	{
		enum
		{
			X_PLACEMENT        = 0x0001,
			Y_PLACEMENT        = 0x0002,
			X_ADVANCE          = 0x0004,
			Y_ADVANCE          = 0x0008,
			X_PLACEMENT_DEVICE = 0x0010,
			Y_PLACEMENT_DEVICE = 0x0020,
			X_ADVANCE_DEVICE   = 0x0040,
			Y_ADVANCE_DEVICE   = 0x0080,
		};

		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			ValueRecord* dst,
			bksge::uint8_t const* start,
			uint16 valueFormat)
		{
			Offset16	xPlaDeviceOffset = 0;
			Offset16	yPlaDeviceOffset = 0;
			Offset16	xAdvDeviceOffset = 0;
			Offset16	yAdvDeviceOffset = 0;

			if (valueFormat & X_PLACEMENT)        { ptr = ReadBigEndian(ptr, &dst->xPlacement); }
			if (valueFormat & Y_PLACEMENT)        { ptr = ReadBigEndian(ptr, &dst->yPlacement); }
			if (valueFormat & X_ADVANCE)          { ptr = ReadBigEndian(ptr, &dst->xAdvance); }
			if (valueFormat & Y_ADVANCE)          { ptr = ReadBigEndian(ptr, &dst->yAdvance); }
			if (valueFormat & X_PLACEMENT_DEVICE) { ptr = ReadBigEndian(ptr, &xPlaDeviceOffset); }
			if (valueFormat & Y_PLACEMENT_DEVICE) { ptr = ReadBigEndian(ptr, &yPlaDeviceOffset); }
			if (valueFormat & X_ADVANCE_DEVICE)   { ptr = ReadBigEndian(ptr, &xAdvDeviceOffset); }
			if (valueFormat & Y_ADVANCE_DEVICE)   { ptr = ReadBigEndian(ptr, &yAdvDeviceOffset); }

			if (xPlaDeviceOffset != 0)
			{
				dst->xPlaDevice = bksge::make_unique<DeviceTable>(
					start + xPlaDeviceOffset);
			}
			if (yPlaDeviceOffset != 0)
			{
				dst->yPlaDevice = bksge::make_unique<DeviceTable>(
					start + yPlaDeviceOffset);
			}
			if (xAdvDeviceOffset != 0)
			{
				dst->xAdvDevice = bksge::make_unique<DeviceTable>(
					start + xAdvDeviceOffset);
			}
			if (yAdvDeviceOffset != 0)
			{
				dst->yAdvDevice = bksge::make_unique<DeviceTable>(
					start + yAdvDeviceOffset);
			}

			return ptr;
		}

		int16		xPlacement = 0;
		int16		yPlacement = 0;
		int16		xAdvance = 0;
		int16		yAdvance = 0;
		bksge::unique_ptr<DeviceTable>	xPlaDevice;
		bksge::unique_ptr<DeviceTable>	yPlaDevice;
		bksge::unique_ptr<DeviceTable>	xAdvDevice;
		bksge::unique_ptr<DeviceTable>	yAdvDevice;
	};

	struct AnchorTable
	{
		explicit AnchorTable(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	xDeviceOffset = 0;	// Format 3
			Offset16	yDeviceOffset = 0;	// Format 3

			ptr = ReadBigEndian(ptr, &anchorFormat);
			ptr = ReadBigEndian(ptr, &xCoordinate);
			ptr = ReadBigEndian(ptr, &yCoordinate);
			if (anchorFormat == 2)
			{
				ptr = ReadBigEndian(ptr, &anchorPoint);
			}
			if (anchorFormat == 3)
			{
				ptr = ReadBigEndian(ptr, &xDeviceOffset);
				ptr = ReadBigEndian(ptr, &yDeviceOffset);
			}

			if (xDeviceOffset != 0)
			{
				xDevice = bksge::make_unique<DeviceTable>(
					start + xDeviceOffset);
			}
			if (yDeviceOffset != 0)
			{
				yDevice = bksge::make_unique<DeviceTable>(
					start + yDeviceOffset);
			}
		}

		uint16							anchorFormat;
		int16							xCoordinate;
		int16							yCoordinate;
		uint16							anchorPoint = 0;// Format 2
		bksge::unique_ptr<DeviceTable>	xDevice;		// Format 3
		bksge::unique_ptr<DeviceTable>	yDevice;		// Format 3
	};

	struct MarkArray
	{
		struct MarkRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				MarkRecord* dst,
				bksge::uint8_t const* start)
			{
				Offset16	markAnchorOffset;
				ptr = ReadBigEndian(ptr, &dst->markClass);
				ptr = ReadBigEndian(ptr, &markAnchorOffset);

				if (markAnchorOffset != 0)
				{
					dst->markAnchor = bksge::make_unique<AnchorTable>(
						start + markAnchorOffset);
				}

				return ptr;
			}

			uint16							markClass;
			bksge::unique_ptr<AnchorTable>	markAnchor;
		};

		explicit MarkArray(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	markCount;
			ptr = ReadBigEndian(ptr, &markCount);
			markRecords.resize(markCount);
			ptr = ReadBigEndian(ptr, &markRecords, start);
		}

		bksge::vector<MarkRecord>	markRecords;
	};

	struct SingleAdjustment : public Lookup::Subtable
	{
		explicit SingleAdjustment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			Offset16	coverageOffset;
			uint16		valueFormat;
			uint16		valueCount;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &valueFormat);

			if (posFormat == 1)
			{
				valueCount = 1;
			}
			else
			{
				ptr = ReadBigEndian(ptr, &valueCount);
			}

			valueRecords.resize(valueCount);
			ptr = ReadBigEndian(ptr, &valueRecords, start, valueFormat);

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<ValueRecord>			valueRecords;
	};

	struct PairAdjustment : public Lookup::Subtable
	{
		struct PairValueRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				PairValueRecord* dst,
				uint16 valueFormat1,
				uint16 valueFormat2)
			{
				auto const start = ptr;
				ptr = ReadBigEndian(ptr, &dst->secondGlyph);
				ptr = ReadBigEndian(ptr, &dst->valueRecord1, start, valueFormat1);
				ptr = ReadBigEndian(ptr, &dst->valueRecord2, start, valueFormat2);
				return ptr;
			}

			uint16		secondGlyph;
			ValueRecord	valueRecord1;
			ValueRecord	valueRecord2;
		};

		struct PairSet
		{
			explicit PairSet(
				bksge::uint8_t const* ptr,
				uint16 valueFormat1,
				uint16 valueFormat2)
			{
				uint16 pairValueCount;
				ptr = ReadBigEndian(ptr, &pairValueCount);
				pairValueRecords.resize(pairValueCount);
				ptr = ReadBigEndian(ptr, &pairValueRecords, valueFormat1, valueFormat2);
			}

			bksge::vector<PairValueRecord>	pairValueRecords;
		};

		struct Format1
		{
			static Format1 Create(
				bksge::uint8_t const* ptr,
				bksge::uint8_t const* start)
			{
				Format1 result;

				Offset16	coverageOffset;
				uint16		valueFormat1;
				uint16		valueFormat2;
				uint16		pairSetCount;

				ptr = ReadBigEndian(ptr, &coverageOffset);
				if (coverageOffset != 0)
				{
					result.coverage = bksge::make_unique<CoverageTable>(
						start + coverageOffset);
				}

				ptr = ReadBigEndian(ptr, &valueFormat1);
				ptr = ReadBigEndian(ptr, &valueFormat2);
				ptr = ReadBigEndian(ptr, &pairSetCount);
				for (uint16 i = 0; i < pairSetCount; ++i)
				{
					Offset16 pairSetOffset;
					ptr = ReadBigEndian(ptr, &pairSetOffset);
					result.pairSets.emplace_back(
						start + pairSetOffset, valueFormat1, valueFormat2);
				}

				return result;
			}

			bksge::unique_ptr<CoverageTable>	coverage;
			bksge::vector<PairSet>				pairSets;
		};

		struct Class2Record
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				Class2Record* dst,
				uint16 valueFormat1,
				uint16 valueFormat2)
			{
				auto const start = ptr;
				ptr = ReadBigEndian(ptr, &dst->valueRecord1, start, valueFormat1);
				ptr = ReadBigEndian(ptr, &dst->valueRecord2, start, valueFormat2);
				return ptr;
			}

			ValueRecord	valueRecord1;
			ValueRecord	valueRecord2;
		};

		struct Class1Record
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				Class1Record* dst,
				uint16 class2Count,
				uint16 valueFormat1,
				uint16 valueFormat2)
			{
				dst->class2Records.resize(class2Count);
				ptr = ReadBigEndian(
					ptr, &dst->class2Records, valueFormat1, valueFormat2);
				return ptr;
			}

			bksge::vector<Class2Record>	class2Records;
		};

		struct Format2
		{
			static Format2 Create(
				bksge::uint8_t const* ptr,
				bksge::uint8_t const* start)
			{
				Format2 result;

				Offset16	coverageOffset;
				uint16		valueFormat1;
				uint16		valueFormat2;
				Offset16	classDef1Offset;
				Offset16	classDef2Offset;
				uint16		class1Count;
				uint16		class2Count;

				ptr = ReadBigEndian(ptr, &coverageOffset);
				ptr = ReadBigEndian(ptr, &valueFormat1);
				ptr = ReadBigEndian(ptr, &valueFormat2);
				ptr = ReadBigEndian(ptr, &classDef1Offset);
				ptr = ReadBigEndian(ptr, &classDef2Offset);
				ptr = ReadBigEndian(ptr, &class1Count);
				ptr = ReadBigEndian(ptr, &class2Count);
				result.class1Records.resize(class1Count);
				ptr = ReadBigEndian(
					ptr, &result.class1Records, class2Count, valueFormat1, valueFormat2);

				if (coverageOffset != 0)
				{
					result.coverage = bksge::make_unique<CoverageTable>(
						start + coverageOffset);
				}
				if (classDef1Offset != 0)
				{
					result.classDef1 = bksge::make_unique<ClassDefinitionTable>(
						start + classDef1Offset);
				}
				if (classDef2Offset != 0)
				{
					result.classDef2 = bksge::make_unique<ClassDefinitionTable>(
						start + classDef2Offset);
				}

				return result;
			}

			bksge::unique_ptr<CoverageTable>		coverage;
			bksge::unique_ptr<ClassDefinitionTable>	classDef1;
			bksge::unique_ptr<ClassDefinitionTable>	classDef2;
			bksge::vector<Class1Record>				class1Records;
		};

		explicit PairAdjustment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16 posFormat;
			ptr = ReadBigEndian(ptr, &posFormat);
			switch (posFormat)
			{
			case 1: value = Format1::Create(ptr, start); break;
			case 2: value = Format2::Create(ptr, start); break;
			}
		}

		bksge::variant<
			Format1,
			Format2
		> value;
	};

	struct CursiveAttachment : public Lookup::Subtable
	{
		struct EntryExitRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				EntryExitRecord* dst,
				bksge::uint8_t const* start)
			{
				Offset16	entryAnchorOffset;
				Offset16	exitAnchorOffset;

				ptr = ReadBigEndian(ptr, &entryAnchorOffset);
				ptr = ReadBigEndian(ptr, &exitAnchorOffset);

				if (entryAnchorOffset != 0)
				{
					dst->entryAnchor = bksge::make_unique<AnchorTable>(
						start + entryAnchorOffset);
				}
				if (exitAnchorOffset != 0)
				{
					dst->exitAnchor = bksge::make_unique<AnchorTable>(
						start + exitAnchorOffset);
				}

				return ptr;
			}

			bksge::unique_ptr<AnchorTable>	entryAnchor;
			bksge::unique_ptr<AnchorTable>	exitAnchor;
		};

		explicit CursiveAttachment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			Offset16	coverageOffset;
			uint16		entryExitCount;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &entryExitCount);
			entryExitRecords.resize(entryExitCount);
			ptr = ReadBigEndian(ptr, &entryExitRecords, start);

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<EntryExitRecord>		entryExitRecords;
	};

	struct MarkToBaseAttachment : public Lookup::Subtable
	{
		struct BaseRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				BaseRecord* dst,
				bksge::uint8_t const* start,
				uint16 markClassCount)
			{
				for (uint16 i = 0; i < markClassCount; ++i)
				{
					Offset16 baseAnchorOffset;
					ptr = ReadBigEndian(ptr, &baseAnchorOffset);

					if (baseAnchorOffset != 0)
					{
						dst->baseAnchors.emplace_back(
							start + baseAnchorOffset);
					}
				}

				return ptr;
			}

			bksge::vector<AnchorTable>	baseAnchors;
		};

		struct BaseArray
		{
			explicit BaseArray(bksge::uint8_t const* ptr, uint16 markClassCount)
			{
				auto const start = ptr;

				uint16	baseCount;
				ptr = ReadBigEndian(ptr, &baseCount);
				baseRecords.resize(baseCount);
				ptr = ReadBigEndian(ptr, &baseRecords, start, markClassCount);
			}

			bksge::vector<BaseRecord>	baseRecords;
		};

		explicit MarkToBaseAttachment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			Offset16	markCoverageOffset;
			Offset16	baseCoverageOffset;
			uint16		markClassCount;
			Offset16	markArrayOffset;
			Offset16	baseArrayOffset;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &markCoverageOffset);
			ptr = ReadBigEndian(ptr, &baseCoverageOffset);
			ptr = ReadBigEndian(ptr, &markClassCount);
			ptr = ReadBigEndian(ptr, &markArrayOffset);
			ptr = ReadBigEndian(ptr, &baseArrayOffset);

			if (markCoverageOffset != 0)
			{
				markCoverage = bksge::make_unique<CoverageTable>(
					start + markCoverageOffset);
			}
			if (baseCoverageOffset != 0)
			{
				baseCoverage = bksge::make_unique<CoverageTable>(
					start + baseCoverageOffset);
			}
			if (markArrayOffset != 0)
			{
				markArray = bksge::make_unique<MarkArray>(
					start + markArrayOffset);
			}
			if (baseArrayOffset != 0)
			{
				baseArray = bksge::make_unique<BaseArray>(
					start + baseArrayOffset, markClassCount);
			}
		}

		bksge::unique_ptr<CoverageTable>	markCoverage;
		bksge::unique_ptr<CoverageTable>	baseCoverage;
		bksge::unique_ptr<MarkArray>		markArray;
		bksge::unique_ptr<BaseArray>		baseArray;
	};

	struct MarkToLigatureAttachment : public Lookup::Subtable
	{
		struct ComponentRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				ComponentRecord* dst,
				bksge::uint8_t const* start,
				uint16 markClassCount)
			{
				for (uint16 i = 0; i < markClassCount; ++i)
				{
					Offset16 ligatureAnchorOffset;
					ptr = ReadBigEndian(ptr, &ligatureAnchorOffset);

					if (ligatureAnchorOffset != 0)
					{
						dst->ligatureAnchors.emplace_back(
							start + ligatureAnchorOffset);
					}
				}

				return ptr;
			}

			bksge::vector<AnchorTable>	ligatureAnchors;
		};

		struct LigatureAttach
		{
			explicit LigatureAttach(bksge::uint8_t const* ptr, uint16 markClassCount)
			{
				auto const start = ptr;

				uint16 componentCount;
				ptr = ReadBigEndian(ptr, &componentCount);
				componentRecords.resize(componentCount);
				ptr = ReadBigEndian(ptr, &componentRecords, start, markClassCount);
			}

			bksge::vector<ComponentRecord>	componentRecords;
		};

		struct LigatureArray
		{
			explicit LigatureArray(bksge::uint8_t const* ptr, uint16 markClassCount)
			{
				auto const start = ptr;

				uint16 ligatureCount;
				ptr = ReadBigEndian(ptr, &ligatureCount);
				for (uint16 i = 0; i < ligatureCount; ++i)
				{
					Offset16 ligatureAttachOffset;
					ptr = ReadBigEndian(ptr, &ligatureAttachOffset);
					ligatureAttachs.emplace_back(
						start + ligatureAttachOffset, markClassCount);
				}
			}

			bksge::vector<LigatureAttach>	ligatureAttachs;
		};

		explicit MarkToLigatureAttachment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			Offset16	markCoverageOffset;
			Offset16	ligatureCoverageOffset;
			uint16		markClassCount;
			Offset16	markArrayOffset;
			Offset16	ligatureArrayOffset;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &markCoverageOffset);
			ptr = ReadBigEndian(ptr, &ligatureCoverageOffset);
			ptr = ReadBigEndian(ptr, &markClassCount);
			ptr = ReadBigEndian(ptr, &markArrayOffset);
			ptr = ReadBigEndian(ptr, &ligatureArrayOffset);

			if (markCoverageOffset != 0)
			{
				markCoverage = bksge::make_unique<CoverageTable>(
					start + markCoverageOffset);
			}
			if (ligatureCoverageOffset != 0)
			{
				ligatureCoverage = bksge::make_unique<CoverageTable>(
					start + ligatureCoverageOffset);
			}
			if (markArrayOffset != 0)
			{
				markArray = bksge::make_unique<MarkArray>(
					start + markArrayOffset);
			}
			if (ligatureArrayOffset != 0)
			{
				ligatureArray = bksge::make_unique<LigatureArray>(
					start + ligatureArrayOffset, markClassCount);
			}
		}

		bksge::unique_ptr<CoverageTable>	markCoverage;
		bksge::unique_ptr<CoverageTable>	ligatureCoverage;
		bksge::unique_ptr<MarkArray>		markArray;
		bksge::unique_ptr<LigatureArray>	ligatureArray;
	};

	struct MarkToMarkAttachment : public Lookup::Subtable
	{
		struct Mark2Record
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				Mark2Record* dst,
				bksge::uint8_t const* start,
				uint16 markClassCount)
			{
				for (uint16 i = 0; i < markClassCount; ++i)
				{
					Offset16 mark2AnchorOffset;
					ptr = ReadBigEndian(ptr, &mark2AnchorOffset);

					if (mark2AnchorOffset != 0)
					{
						dst->mark2Anchors.emplace_back(
							start + mark2AnchorOffset);
					}
				}

				return ptr;
			}

			bksge::vector<AnchorTable>	mark2Anchors;
		};

		struct Mark2Array
		{
			explicit Mark2Array(bksge::uint8_t const* ptr, uint16 markClassCount)
			{
				auto const start = ptr;

				uint16	mark2Count;
				ptr = ReadBigEndian(ptr, &mark2Count);
				mark2Records.resize(mark2Count);
				ptr = ReadBigEndian(ptr, &mark2Records, start, markClassCount);
			}

			bksge::vector<Mark2Record>	mark2Records;
		};

		explicit MarkToMarkAttachment(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			Offset16	mark1CoverageOffset;
			Offset16	mark2CoverageOffset;
			uint16		markClassCount;
			Offset16	mark1ArrayOffset;
			Offset16	mark2ArrayOffset;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &mark1CoverageOffset);
			ptr = ReadBigEndian(ptr, &mark2CoverageOffset);
			ptr = ReadBigEndian(ptr, &markClassCount);
			ptr = ReadBigEndian(ptr, &mark1ArrayOffset);
			ptr = ReadBigEndian(ptr, &mark2ArrayOffset);

			if (mark1CoverageOffset != 0)
			{
				mark1Coverage = bksge::make_unique<CoverageTable>(
					start + mark1CoverageOffset);
			}
			if (mark2CoverageOffset != 0)
			{
				mark2Coverage = bksge::make_unique<CoverageTable>(
					start + mark2CoverageOffset);
			}
			if (mark1ArrayOffset != 0)
			{
				mark1Array = bksge::make_unique<MarkArray>(
					start + mark1ArrayOffset);
			}
			if (mark2ArrayOffset != 0)
			{
				mark2Array = bksge::make_unique<Mark2Array>(
					start + mark2ArrayOffset, markClassCount);
			}
		}

		bksge::unique_ptr<CoverageTable>	mark1Coverage;
		bksge::unique_ptr<CoverageTable>	mark2Coverage;
		bksge::unique_ptr<MarkArray>		mark1Array;
		bksge::unique_ptr<Mark2Array>		mark2Array;
	};

	struct ContextPositioning : public Lookup::Subtable
	{
		explicit ContextPositioning(bksge::uint8_t const* ptr)
			: sequenceContext(ptr)
		{}

		SequenceContext sequenceContext;
	};

	struct ChainedContextPositioning : public Lookup::Subtable
	{
		explicit ChainedContextPositioning(bksge::uint8_t const* ptr)
			: chainedSequenceContext(ptr)
		{}

		ChainedSequenceContext chainedSequenceContext;
	};

	struct ExtensionPositioning : public Lookup::Subtable
	{
		explicit ExtensionPositioning(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		posFormat;
			uint16		extensionLookupType;
			Offset32	extensionOffset;

			ptr = ReadBigEndian(ptr, &posFormat);
			ptr = ReadBigEndian(ptr, &extensionLookupType);
			ptr = ReadBigEndian(ptr, &extensionOffset);

			extension = CreateSubtable(extensionLookupType, start + extensionOffset);
		}

		bksge::unique_ptr<Lookup::Subtable>	extension;
	};

	static bksge::unique_ptr<Lookup::Subtable>
	CreateSubtable(uint16 lookupType, bksge::uint8_t const* ptr)
	{
		switch (lookupType)
		{
		case 1:	return bksge::make_unique<SingleAdjustment>(ptr);
		case 2:	return bksge::make_unique<PairAdjustment>(ptr);
		case 3:	return bksge::make_unique<CursiveAttachment>(ptr);
		case 4:	return bksge::make_unique<MarkToBaseAttachment>(ptr);
		case 5:	return bksge::make_unique<MarkToLigatureAttachment>(ptr);
		case 6:	return bksge::make_unique<MarkToMarkAttachment>(ptr);
		case 7:	return bksge::make_unique<ContextPositioning>(ptr);
		case 8:	return bksge::make_unique<ChainedContextPositioning>(ptr);
		case 9:	return bksge::make_unique<ExtensionPositioning>(ptr);
		}
		return {};
	}

	explicit GlyphPositioningTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset16	scriptListOffset        = 0;
		Offset16	featureListOffset       = 0;
		Offset16	lookupListOffset        = 0;
		Offset32	featureVariationsOffset = 0;	// Version 1.1

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &scriptListOffset);
		ptr = ReadBigEndian(ptr, &featureListOffset);
		ptr = ReadBigEndian(ptr, &lookupListOffset);
		if (majorVersion == 1 && minorVersion == 1)
		{
			ptr = ReadBigEndian(ptr, &featureVariationsOffset);
		}

		if (scriptListOffset != 0)
		{
			scriptList = bksge::make_unique<ScriptList>(
				start + scriptListOffset);
		}
		if (featureListOffset != 0)
		{
			featureList = bksge::make_unique<FeatureList>(
				start + featureListOffset);
		}
		if (lookupListOffset != 0)
		{
			lookupList = bksge::make_unique<LookupList>(
				start + lookupListOffset, CreateSubtable);
		}
		if (featureVariationsOffset != 0)
		{
			featureVariations = bksge::make_unique<FeatureVariations>(
				start + featureVariationsOffset);
		}
	}

	bksge::unique_ptr<ScriptList>			scriptList;
	bksge::unique_ptr<FeatureList>			featureList;
	bksge::unique_ptr<LookupList>			lookupList;
	bksge::unique_ptr<FeatureVariations>	featureVariations;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_GPOS_HPP
