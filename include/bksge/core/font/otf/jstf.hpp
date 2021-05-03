/**
 *	@file	jstf.hpp
 *
 *	@brief	JustificationTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_JSTF_HPP
#define BKSGE_CORE_FONT_OTF_JSTF_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/lookup.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct JustificationTable
{
	struct ExtenderGlyph
	{
		explicit ExtenderGlyph(bksge::uint8_t const* ptr)
		{
			uint16	glyphCount;
			ptr = ReadBigEndian(ptr, &glyphCount);
			extenderGlyphs.resize(glyphCount);
			ptr = ReadBigEndian(ptr, &extenderGlyphs);
		}

		bksge::vector<uint16>	extenderGlyphs;
	};

	struct JstfGSUBModList
	{
		explicit JstfGSUBModList(bksge::uint8_t const* ptr)
		{
			uint16	lookupCount;
			ptr = ReadBigEndian(ptr, &lookupCount);
			gsubLookupIndices.resize(lookupCount);
			ptr = ReadBigEndian(ptr, &gsubLookupIndices);
		}

		bksge::vector<uint16>	gsubLookupIndices;
	};

	struct JstfGPOSModList
	{
		explicit JstfGPOSModList(bksge::uint8_t const* ptr)
		{
			uint16	lookupCount;
			ptr = ReadBigEndian(ptr, &lookupCount);
			gposLookupIndices.resize(lookupCount);
			ptr = ReadBigEndian(ptr, &gposLookupIndices);
		}

		bksge::vector<uint16>	gposLookupIndices;
	};

	struct JstfMax
	{
		explicit JstfMax(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16 lookupCount;
			ptr = ReadBigEndian(ptr, &lookupCount);
			for (uint16 i = 0; i < lookupCount; ++i)
			{
				Offset16 lookupOffset;
				ptr = ReadBigEndian(ptr, &lookupOffset);
				lookups.emplace_back(
					start + lookupOffset,
					GlyphPositioningTable::CreateSubtable);
			}
		}

		bksge::vector<Lookup>	lookups;
	};

	struct JstfPriority
	{
		explicit JstfPriority(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	gsubShrinkageEnableOffset;
			Offset16	gsubShrinkageDisableOffset;
			Offset16	gposShrinkageEnableOffset;
			Offset16	gposShrinkageDisableOffset;
			Offset16	shrinkageJstfMaxOffset;
			Offset16	gsubExtensionEnableOffset;
			Offset16	gsubExtensionDisableOffset;
			Offset16	gposExtensionEnableOffset;
			Offset16	gposExtensionDisableOffset;
			Offset16	extensionJstfMaxOffset;

			ptr = ReadBigEndian(ptr, &gsubShrinkageEnableOffset);
			ptr = ReadBigEndian(ptr, &gsubShrinkageDisableOffset);
			ptr = ReadBigEndian(ptr, &gposShrinkageEnableOffset);
			ptr = ReadBigEndian(ptr, &gposShrinkageDisableOffset);
			ptr = ReadBigEndian(ptr, &shrinkageJstfMaxOffset);
			ptr = ReadBigEndian(ptr, &gsubExtensionEnableOffset);
			ptr = ReadBigEndian(ptr, &gsubExtensionDisableOffset);
			ptr = ReadBigEndian(ptr, &gposExtensionEnableOffset);
			ptr = ReadBigEndian(ptr, &gposExtensionDisableOffset);
			ptr = ReadBigEndian(ptr, &extensionJstfMaxOffset);

			if (gsubShrinkageEnableOffset != 0)
			{
				gsubShrinkageEnable = bksge::make_unique<JstfGSUBModList>(
					start + gsubShrinkageEnableOffset);
			}
			if (gsubShrinkageDisableOffset != 0)
			{
				gsubShrinkageDisable = bksge::make_unique<JstfGSUBModList>(
					start + gsubShrinkageDisableOffset);
			}
			if (gposShrinkageEnableOffset != 0)
			{
				gposShrinkageEnable = bksge::make_unique<JstfGPOSModList>(
					start + gposShrinkageEnableOffset);
			}
			if (gposShrinkageDisableOffset != 0)
			{
				gposShrinkageDisable = bksge::make_unique<JstfGPOSModList>(
					start + gposShrinkageDisableOffset);
			}
			if (shrinkageJstfMaxOffset != 0)
			{
				shrinkageJstfMax = bksge::make_unique<JstfMax>(
					start + shrinkageJstfMaxOffset);
			}
			if (gsubExtensionEnableOffset != 0)
			{
				gsubExtensionEnable = bksge::make_unique<JstfGSUBModList>(
					start + gsubExtensionEnableOffset);
			}
			if (gsubExtensionDisableOffset != 0)
			{
				gsubExtensionDisable = bksge::make_unique<JstfGSUBModList>(
					start + gsubExtensionDisableOffset);
			}
			if (gposExtensionEnableOffset != 0)
			{
				gposExtensionEnable = bksge::make_unique<JstfGPOSModList>(
					start + gposExtensionEnableOffset);
			}
			if (gposExtensionDisableOffset != 0)
			{
				gposExtensionDisable = bksge::make_unique<JstfGPOSModList>(
					start + gposExtensionDisableOffset);
			}
			if (extensionJstfMaxOffset != 0)
			{
				extensionJstfMax = bksge::make_unique<JstfMax>(
					start + extensionJstfMaxOffset);
			}
		}

		bksge::unique_ptr<JstfGSUBModList>	gsubShrinkageEnable;
		bksge::unique_ptr<JstfGSUBModList>	gsubShrinkageDisable;
		bksge::unique_ptr<JstfGPOSModList>	gposShrinkageEnable;
		bksge::unique_ptr<JstfGPOSModList>	gposShrinkageDisable;
		bksge::unique_ptr<JstfMax>			shrinkageJstfMax;
		bksge::unique_ptr<JstfGSUBModList>	gsubExtensionEnable;
		bksge::unique_ptr<JstfGSUBModList>	gsubExtensionDisable;
		bksge::unique_ptr<JstfGPOSModList>	gposExtensionEnable;
		bksge::unique_ptr<JstfGPOSModList>	gposExtensionDisable;
		bksge::unique_ptr<JstfMax>			extensionJstfMax;
	};

	struct JstfLangSys
	{
		explicit JstfLangSys(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	jstfPriorityCount;
			ptr = ReadBigEndian(ptr, &jstfPriorityCount);
			for (uint16 i = 0; i < jstfPriorityCount; ++i)
			{
				Offset16 jstfPriorityOffset;
				ptr = ReadBigEndian(ptr, &jstfPriorityOffset);
				jstfPrioritys.emplace_back(start + jstfPriorityOffset);
			}
		}

		bksge::vector<JstfPriority>	jstfPrioritys;
	};

	struct JstfLangSysRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			JstfLangSysRecord* dst,
			bksge::uint8_t const* start)
		{
			Offset16 jstfLangSysOffset;
			ptr = ReadBigEndian(ptr, &dst->jstfLangSysTag);
			ptr = ReadBigEndian(ptr, &jstfLangSysOffset);
			if (jstfLangSysOffset != 0)
			{
				dst->jstfLangSys = bksge::make_unique<JstfLangSys>(
					start + jstfLangSysOffset);
			}
			return ptr;
		}

		Tag								jstfLangSysTag;
		bksge::unique_ptr<JstfLangSys>	jstfLangSys;
	};

	struct JstfScript
	{
		explicit JstfScript(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	extenderGlyphOffset;
			Offset16	defJstfLangSysOffset;
			uint16		jstfLangSysCount;

			ptr = ReadBigEndian(ptr, &extenderGlyphOffset);
			ptr = ReadBigEndian(ptr, &defJstfLangSysOffset);
			ptr = ReadBigEndian(ptr, &jstfLangSysCount);
			jstfLangSysRecords.resize(jstfLangSysCount);
			ptr = ReadBigEndian(ptr, &jstfLangSysRecords, start);

			if (extenderGlyphOffset != 0)
			{
				extenderGlyph = bksge::make_unique<ExtenderGlyph>(
					start + extenderGlyphOffset);
			}
			if (defJstfLangSysOffset != 0)
			{
				defJstfLangSys = bksge::make_unique<JstfLangSys>(
					start + defJstfLangSysOffset);
			}
		}

		bksge::unique_ptr<ExtenderGlyph>	extenderGlyph;
		bksge::unique_ptr<JstfLangSys>		defJstfLangSys;
		bksge::vector<JstfLangSysRecord>	jstfLangSysRecords;
	};

	struct JstfScriptRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			JstfScriptRecord* dst,
			bksge::uint8_t const* start)
		{
			Offset16 jstfScriptOffset;
			ptr = ReadBigEndian(ptr, &dst->jstfScriptTag);
			ptr = ReadBigEndian(ptr, &jstfScriptOffset);
			if (jstfScriptOffset != 0)
			{
				dst->jstfScript = bksge::make_unique<JstfScript>(
					start + jstfScriptOffset);
			}
			return ptr;
		}

		Tag								jstfScriptTag;
		bksge::unique_ptr<JstfScript>	jstfScript;
	};

	explicit JustificationTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16	majorVersion;
		uint16	minorVersion;
		uint16	jstfScriptCount;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &jstfScriptCount);
		jstfScriptRecords.resize(jstfScriptCount);
		ptr = ReadBigEndian(ptr, &jstfScriptRecords, start);
	}

	bksge::vector<JstfScriptRecord>		jstfScriptRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_JSTF_HPP
