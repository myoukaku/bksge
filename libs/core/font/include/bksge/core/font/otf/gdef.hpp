/**
 *	@file	gdef.hpp
 *
 *	@brief	GlyphDefinitionTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GDEF_HPP
#define BKSGE_CORE_FONT_OTF_GDEF_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/class_definition_table.hpp>
#include <bksge/core/font/otf/coverage_table.hpp>
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

struct GlyphDefinitionTable
{
	struct GlyphClassDef : public ClassDefinitionTable
	{
		explicit GlyphClassDef(std::uint8_t const* ptr)
			: ClassDefinitionTable(ptr)
		{}
	};

	struct AttachList
	{
		struct AttachPoint
		{
			explicit AttachPoint(std::uint8_t const* ptr)
			{
				uint16	pointCount;
				ptr = ReadBigEndian(ptr, &pointCount);
				pointIndices.resize(pointCount);
				ptr = ReadBigEndian(ptr, &pointIndices);
			}

			bksge::vector<uint16>	pointIndices;
		};

		explicit AttachList(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	coverageOffset;
			uint16		glyphCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &glyphCount);
			for (uint16 i = 0; i < glyphCount; ++i)
			{
				Offset16 attachPointOffset;
				ptr = ReadBigEndian(ptr, &attachPointOffset);
				attachPoints.emplace_back(start + attachPointOffset);
			}

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<AttachPoint>			attachPoints;
	};

	struct LigCaretList
	{
		struct CaretValue
		{
			struct Format1
			{
				static Format1 Create(std::uint8_t const* ptr)
				{
					Format1 result;
					ptr = ReadBigEndian(ptr, &result.coordinate);
					return result;
				}

				int16	coordinate;
			};

			struct Format2
			{
				static Format2 Create(std::uint8_t const* ptr)
				{
					Format2 result;
					ptr = ReadBigEndian(ptr, &result.caretValuePointIndex);
					return result;
				}

				uint16	caretValuePointIndex;
			};

			struct Format3
			{
				static Format3 Create(
					std::uint8_t const* ptr,
					std::uint8_t const* start)
				{
					Format3 result;

					Offset16 deviceOffset = 0;

					ptr = ReadBigEndian(ptr, &result.coordinate);
					ptr = ReadBigEndian(ptr, &deviceOffset);

					if (deviceOffset != 0)
					{
						result.device = bksge::make_unique<DeviceTable>(
							start + deviceOffset);
					}

					return result;
				}

				int16							coordinate;
				bksge::unique_ptr<DeviceTable>	device;
			};

			explicit CaretValue(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	caretValueFormat;
				ptr = ReadBigEndian(ptr, &caretValueFormat);
				switch (caretValueFormat)
				{
				case 1: value = Format1::Create(ptr); break;
				case 2: value = Format2::Create(ptr); break;
				case 3: value = Format3::Create(ptr, start); break;
				}
			}

			bksge::variant<
				Format1,
				Format2,
				Format3
			> value;
		};

		struct LigGlyph
		{
			explicit LigGlyph(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16 caretCount;
				ptr = ReadBigEndian(ptr, &caretCount);
				for (uint16 i = 0; i < caretCount; ++i)
				{
					Offset16 caretValueOffset;
					ptr = ReadBigEndian(ptr, &caretValueOffset);
					caretValues.emplace_back(start + caretValueOffset);
				}
			}

			bksge::vector<CaretValue>	caretValues;
		};

		explicit LigCaretList(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	coverageOffset;
			uint16		ligGlyphCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &ligGlyphCount);
			for (uint16 i = 0; i < ligGlyphCount; ++i)
			{
				Offset16 ligGlyphOffset;
				ptr = ReadBigEndian(ptr, &ligGlyphOffset);
				ligGlyphs.emplace_back(start + ligGlyphOffset);
			}

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<LigGlyph>				ligGlyphs;
	};

	struct MarkAttachClassDef : public ClassDefinitionTable
	{
		explicit MarkAttachClassDef(std::uint8_t const* ptr)
			: ClassDefinitionTable(ptr)
		{}
	};

	struct MarkGlyphSetsDef
	{
		explicit MarkGlyphSetsDef(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	format;
			uint16	markGlyphSetCount;

			ptr = ReadBigEndian(ptr, &format);
			ptr = ReadBigEndian(ptr, &markGlyphSetCount);
			for (uint16 i = 0; i < markGlyphSetCount; ++i)
			{
				Offset32 coverageOffset;
				ptr = ReadBigEndian(ptr, &coverageOffset);
				coverages.emplace_back(start + coverageOffset);
			}
		}

		bksge::vector<CoverageTable>	coverages;
	};

	explicit GlyphDefinitionTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset16	glyphClassDefOffset      = 0;
		Offset16	attachListOffset         = 0;
		Offset16	ligCaretListOffset       = 0;
		Offset16	markAttachClassDefOffset = 0;
		Offset16	markGlyphSetsDefOffset   = 0;	// Version 1.2
		Offset32	itemVarStoreOffset       = 0;	// Version 1.3

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &glyphClassDefOffset);
		ptr = ReadBigEndian(ptr, &attachListOffset);
		ptr = ReadBigEndian(ptr, &ligCaretListOffset);
		ptr = ReadBigEndian(ptr, &markAttachClassDefOffset);
		if (majorVersion == 1 && minorVersion >= 2)
		{
			ptr = ReadBigEndian(ptr, &markGlyphSetsDefOffset);
		}
		if (majorVersion == 1 && minorVersion >= 3)
		{
			ptr = ReadBigEndian(ptr, &itemVarStoreOffset);
		}

		if (glyphClassDefOffset != 0)
		{
			glyphClassDef = bksge::make_unique<GlyphClassDef>(
				start + glyphClassDefOffset);
		}
		if (attachListOffset != 0)
		{
			attachList = bksge::make_unique<AttachList>(
				start + attachListOffset);
		}
		if (ligCaretListOffset != 0)
		{
			ligCaretList = bksge::make_unique<LigCaretList>(
				start + ligCaretListOffset);
		}
		if (markAttachClassDefOffset != 0)
		{
			markAttachClassDef = bksge::make_unique<MarkAttachClassDef>(
				start + markAttachClassDefOffset);
		}
		if (markGlyphSetsDefOffset != 0)
		{
			markGlyphSetsDef = bksge::make_unique<MarkGlyphSetsDef>(
				start + markGlyphSetsDefOffset);
		}
		if (itemVarStoreOffset != 0)
		{
			itemVarStore = bksge::make_unique<ItemVariationStore>(
				start + itemVarStoreOffset);
		}
	}

	bksge::unique_ptr<GlyphClassDef>		glyphClassDef;
	bksge::unique_ptr<AttachList>			attachList;
	bksge::unique_ptr<LigCaretList>			ligCaretList;
	bksge::unique_ptr<MarkAttachClassDef>	markAttachClassDef;
	bksge::unique_ptr<MarkGlyphSetsDef>		markGlyphSetsDef;	// Version 1.2
	bksge::unique_ptr<ItemVariationStore>	itemVarStore;		// Version 1.3
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_GDEF_HPP
