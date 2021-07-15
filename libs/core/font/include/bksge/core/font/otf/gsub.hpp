/**
 *	@file	gsub.hpp
 *
 *	@brief	GlyphSubstitutionTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GSUB_HPP
#define BKSGE_CORE_FONT_OTF_GSUB_HPP

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
#include <cstdint>

namespace bksge
{

namespace otf
{

struct GlyphSubstitutionTable
{
	struct SingleSubstitution : public Lookup::Subtable
	{
		struct Format1
		{
			static Format1 Create(
				std::uint8_t const* ptr,
				std::uint8_t const* start)
			{
				Format1 result;

				Offset16 coverageOffset;
				ptr = ReadBigEndian(ptr, &coverageOffset);
				ptr = ReadBigEndian(ptr, &result.deltaGlyphID);

				if (coverageOffset != 0)
				{
					result.coverage = bksge::make_unique<CoverageTable>(
						start + coverageOffset);
				}

				return result;
			}

			bksge::unique_ptr<CoverageTable>	coverage;
			int16								deltaGlyphID;
		};

		struct Format2
		{
			static Format2 Create(
				std::uint8_t const* ptr,
				std::uint8_t const* start)
			{
				Format2 result;

				Offset16	coverageOffset;
				uint16		glyphCount;

				ptr = ReadBigEndian(ptr, &coverageOffset);
				ptr = ReadBigEndian(ptr, &glyphCount);
				result.substituteGlyphIDs.resize(glyphCount);
				ptr = ReadBigEndian(ptr, &result.substituteGlyphIDs);

				if (coverageOffset != 0)
				{
					result.coverage = bksge::make_unique<CoverageTable>(
						start + coverageOffset);
				}

				return result;
			}

			bksge::unique_ptr<CoverageTable>	coverage;
			bksge::vector<uint16>				substituteGlyphIDs;
		};

		explicit SingleSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16 substFormat;
			ptr = ReadBigEndian(ptr, &substFormat);
			switch (substFormat)
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

	struct MultipleSubstitution : public Lookup::Subtable
	{
		struct Sequence
		{
			explicit Sequence(std::uint8_t const* ptr)
			{
				uint16	glyphCount;

				ptr = ReadBigEndian(ptr, &glyphCount);
				substituteGlyphIDs.resize(glyphCount);
				ptr = ReadBigEndian(ptr, &substituteGlyphIDs);
			}

			bksge::vector<uint16>	substituteGlyphIDs;
		};

		explicit MultipleSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		substFormat;
			Offset16	coverageOffset;
			uint16		sequenceCount;

			ptr = ReadBigEndian(ptr, &substFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &sequenceCount);

			for (uint16 i = 0; i < sequenceCount; ++i)
			{
				Offset16 sequenceOffset;
				ptr = ReadBigEndian(ptr, &sequenceOffset);
				sequence.emplace_back(start + sequenceOffset);
			}

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<Sequence>				sequence;
	};

	struct AlternateSubstitution : public Lookup::Subtable
	{
		struct AlternateSet
		{
			explicit AlternateSet(std::uint8_t const* ptr)
			{
				uint16	glyphCount;

				ptr = ReadBigEndian(ptr, &glyphCount);
				alternateGlyphIDs.resize(glyphCount);
				ptr = ReadBigEndian(ptr, &alternateGlyphIDs);
			}

			bksge::vector<uint16>	alternateGlyphIDs;
		};

		explicit AlternateSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		substFormat;
			Offset16	coverageOffset;
			uint16		alternateSetCount;

			ptr = ReadBigEndian(ptr, &substFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &alternateSetCount);
			for (uint16 i = 0; i < alternateSetCount; ++i)
			{
				Offset16 alternateSetOffset;
				ptr = ReadBigEndian(ptr, &alternateSetOffset);
				alternateSets.emplace_back(start + alternateSetOffset);
			}

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<AlternateSet>			alternateSets;
	};

	struct LigatureSubstitution : public Lookup::Subtable
	{
		struct Ligature
		{
			explicit Ligature(std::uint8_t const* ptr)
			{
				uint16	componentCount;
				ptr = ReadBigEndian(ptr, &ligatureGlyph);
				ptr = ReadBigEndian(ptr, &componentCount);
				componentGlyphIDs.resize(componentCount - 1);
				ptr = ReadBigEndian(ptr, &componentGlyphIDs);
			}

			uint16					ligatureGlyph;
			bksge::vector<uint16>	componentGlyphIDs;
		};

		struct LigatureSet
		{
			explicit LigatureSet(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	ligatureCount;
				ptr = ReadBigEndian(ptr, &ligatureCount);
				for (uint16 i = 0; i < ligatureCount; ++i)
				{
					Offset16 ligatureOffset;
					ptr = ReadBigEndian(ptr, &ligatureOffset);
					ligatures.emplace_back(start + ligatureOffset);
				}
			}

			bksge::vector<Ligature>		ligatures;
		};

		explicit LigatureSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		substFormat;
			Offset16	coverageOffset;
			uint16		ligatureSetCount;

			ptr = ReadBigEndian(ptr, &substFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &ligatureSetCount);
			for (uint16 i = 0; i < ligatureSetCount; ++i)
			{
				Offset16 ligatureSetOffset;
				ptr = ReadBigEndian(ptr, &ligatureSetOffset);
				ligatureSets.emplace_back(start + ligatureSetOffset);
			}

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<LigatureSet>			ligatureSets;
	};

	struct ContextualSubstitution : public Lookup::Subtable
	{
		explicit ContextualSubstitution(std::uint8_t const* ptr)
			: sequenceContext(ptr)
		{}

		SequenceContext sequenceContext;
	};

	struct ChainedContextsSubstitution : public Lookup::Subtable
	{
		explicit ChainedContextsSubstitution(std::uint8_t const* ptr)
			: chainedSequenceContext(ptr)
		{}

		ChainedSequenceContext chainedSequenceContext;
	};

	struct ExtensionSubstitution : public Lookup::Subtable
	{
		explicit ExtensionSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		substFormat;
			uint16		extensionLookupType;
			Offset32	extensionOffset;

			ptr = ReadBigEndian(ptr, &substFormat);
			ptr = ReadBigEndian(ptr, &extensionLookupType);
			ptr = ReadBigEndian(ptr, &extensionOffset);

			extension = CreateSubtable(extensionLookupType, start + extensionOffset);
		}

		bksge::unique_ptr<Lookup::Subtable>	extension;
	};

	struct ReverseChainingContextualSingleSubstitution : public Lookup::Subtable
	{
		explicit ReverseChainingContextualSingleSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16		substFormat;
			Offset16	coverageOffset;
			uint16		backtrackGlyphCount;
			uint16		lookaheadGlyphCount;
			uint16		glyphCount;

			ptr = ReadBigEndian(ptr, &substFormat);
			ptr = ReadBigEndian(ptr, &coverageOffset);

			ptr = ReadBigEndian(ptr, &backtrackGlyphCount);
			for (uint16 i = 0; i < backtrackGlyphCount; ++i)
			{
				Offset16	backtrackCoverageOffset;
				ptr = ReadBigEndian(ptr, &backtrackCoverageOffset);
				backtrackCoverages.emplace_back(start + backtrackCoverageOffset);
			}

			ptr = ReadBigEndian(ptr, &lookaheadGlyphCount);
			for (uint16 i = 0; i < lookaheadGlyphCount; ++i)
			{
				Offset16	lookaheadCoverageOffset;
				ptr = ReadBigEndian(ptr, &lookaheadCoverageOffset);
				lookaheadCoverages.emplace_back(start + lookaheadCoverageOffset);
			}

			ptr = ReadBigEndian(ptr, &glyphCount);
			substituteGlyphIDs.resize(glyphCount);
			ptr = ReadBigEndian(ptr, &substituteGlyphIDs);

			if (coverageOffset != 0)
			{
				coverage = bksge::make_unique<CoverageTable>(start + coverageOffset);
			}
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<CoverageTable>		backtrackCoverages;
		bksge::vector<CoverageTable>		lookaheadCoverages;
		bksge::vector<uint16>				substituteGlyphIDs;
	};

	static bksge::unique_ptr<Lookup::Subtable>
	CreateSubtable(uint16 lookupType, std::uint8_t const* ptr)
	{
		switch (lookupType)
		{
		case 1:	return bksge::make_unique<SingleSubstitution>(ptr);
		case 2:	return bksge::make_unique<MultipleSubstitution>(ptr);
		case 3:	return bksge::make_unique<AlternateSubstitution>(ptr);
		case 4:	return bksge::make_unique<LigatureSubstitution>(ptr);
		case 5:	return bksge::make_unique<ContextualSubstitution>(ptr);
		case 6:	return bksge::make_unique<ChainedContextsSubstitution>(ptr);
		case 7:	return bksge::make_unique<ExtensionSubstitution>(ptr);
		case 8:	return bksge::make_unique<ReverseChainingContextualSingleSubstitution>(ptr);
		}
		return {};
	}

	explicit GlyphSubstitutionTable(std::uint8_t const* ptr)
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

#endif // BKSGE_CORE_FONT_OTF_GSUB_HPP
