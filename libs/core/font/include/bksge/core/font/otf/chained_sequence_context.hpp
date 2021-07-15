/**
 *	@file	chained_sequence_context.hpp
 *
 *	@brief	ChainedSequenceContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CHAINED_SEQUENCE_CONTEXT_HPP
#define BKSGE_CORE_FONT_OTF_CHAINED_SEQUENCE_CONTEXT_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/coverage_table.hpp>
#include <bksge/core/font/otf/sequence_lookup_record.hpp>
#include <bksge/core/font/otf/class_definition_table.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct ChainedSequenceContext
{
	struct Format1
	{
		struct ChainedSequenceRule
		{
			explicit ChainedSequenceRule(std::uint8_t const* ptr)
			{
				uint16	backtrackGlyphCount;
				uint16	inputGlyphCount;
				uint16	lookaheadGlyphCount;
				uint16	seqLookupCount;

				ptr = ReadBigEndian(ptr, &backtrackGlyphCount);
				backtrackSequence.resize(backtrackGlyphCount);
				ptr = ReadBigEndian(ptr, &backtrackSequence);

				ptr = ReadBigEndian(ptr, &inputGlyphCount);
				inputSequence.resize(inputGlyphCount - 1);
				ptr = ReadBigEndian(ptr, &inputSequence);

				ptr = ReadBigEndian(ptr, &lookaheadGlyphCount);
				lookaheadSequence.resize(lookaheadGlyphCount);
				ptr = ReadBigEndian(ptr, &lookaheadSequence);

				ptr = ReadBigEndian(ptr, &seqLookupCount);
				seqLookupRecords.resize(seqLookupCount);
				ptr = ReadBigEndian(ptr, &seqLookupRecords);
			}

			bksge::vector<uint16>				backtrackSequence;
			bksge::vector<uint16>				inputSequence;
			bksge::vector<uint16>				lookaheadSequence;
			bksge::vector<SequenceLookupRecord>	seqLookupRecords;
		};

		struct ChainedSequenceRuleSet
		{
			explicit ChainedSequenceRuleSet(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16 chainedSeqRuleCount;
				ptr = ReadBigEndian(ptr, &chainedSeqRuleCount);
				for (uint16 i = 0; i < chainedSeqRuleCount; ++i)
				{
					Offset16 chainedSeqRuleOffset;
					ptr = ReadBigEndian(ptr, &chainedSeqRuleOffset);
					chainedSeqRules.emplace_back(start + chainedSeqRuleOffset);
				}
			}

			bksge::vector<ChainedSequenceRule>	chainedSeqRules;
		};

		static Format1 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format1 result;

			Offset16	coverageOffset;
			uint16		chainedSeqRuleSetCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &chainedSeqRuleSetCount);
			for (uint16 i = 0; i < chainedSeqRuleSetCount; ++i)
			{
				Offset16	chainedSeqRuleSetOffset;
				ptr = ReadBigEndian(ptr, &chainedSeqRuleSetOffset);
				result.chainedSeqRuleSets.emplace_back(
					start + chainedSeqRuleSetOffset);
			}

			if (coverageOffset != 0)
			{
				result.coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}

			return result;
		}

		bksge::unique_ptr<CoverageTable>		coverage;
		bksge::vector<ChainedSequenceRuleSet>	chainedSeqRuleSets;

	};

	struct Format2
	{
		struct ChainedClassSequenceRule
		{
			explicit ChainedClassSequenceRule(std::uint8_t const* ptr)
			{
				uint16	backtrackGlyphCount;
				uint16	inputGlyphCount;
				uint16	lookaheadGlyphCount;
				uint16	seqLookupCount;

				ptr = ReadBigEndian(ptr, &backtrackGlyphCount);
				backtrackSequence.resize(backtrackGlyphCount);
				ptr = ReadBigEndian(ptr, &backtrackSequence);

				ptr = ReadBigEndian(ptr, &inputGlyphCount);
				inputSequence.resize(inputGlyphCount - 1);
				ptr = ReadBigEndian(ptr, &inputSequence);

				ptr = ReadBigEndian(ptr, &lookaheadGlyphCount);
				lookaheadSequence.resize(lookaheadGlyphCount);
				ptr = ReadBigEndian(ptr, &lookaheadSequence);

				ptr = ReadBigEndian(ptr, &seqLookupCount);
				seqLookupRecords.resize(seqLookupCount);
				ptr = ReadBigEndian(ptr, &seqLookupRecords);
			}

			bksge::vector<uint16>				backtrackSequence;
			bksge::vector<uint16>				inputSequence;
			bksge::vector<uint16>				lookaheadSequence;
			bksge::vector<SequenceLookupRecord>	seqLookupRecords;
		};

		struct ChainedClassSequenceRuleSet
		{
			explicit ChainedClassSequenceRuleSet(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	chainedClassSeqRuleCount;
				ptr = ReadBigEndian(ptr, &chainedClassSeqRuleCount);
				for (uint16 i = 0; i < chainedClassSeqRuleCount; ++i)
				{
					Offset16 chainedClassSeqRuleOffset;
					ptr = ReadBigEndian(ptr, &chainedClassSeqRuleOffset);
					chainedClassSeqRules.emplace_back(
						start + chainedClassSeqRuleOffset);
				}
			}

			bksge::vector<ChainedClassSequenceRule>	chainedClassSeqRules;
		};

		static Format2 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format2 result;

			Offset16	coverageOffset;
			Offset16	backtrackClassDefOffset;
			Offset16	inputClassDefOffset;
			Offset16	lookaheadClassDefOffset;
			uint16		chainedClassSeqRuleSetCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &backtrackClassDefOffset);
			ptr = ReadBigEndian(ptr, &inputClassDefOffset);
			ptr = ReadBigEndian(ptr, &lookaheadClassDefOffset);
			ptr = ReadBigEndian(ptr, &chainedClassSeqRuleSetCount);
			for (uint16 i = 0; i < chainedClassSeqRuleSetCount; ++i)
			{
				Offset16 chainedClassSeqRuleSetOffset;
				ptr = ReadBigEndian(ptr, &chainedClassSeqRuleSetOffset);
				result.chainedClassSeqRuleSets.emplace_back(
					start + chainedClassSeqRuleSetOffset);
			}

			if (coverageOffset != 0)
			{
				result.coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
			if (backtrackClassDefOffset != 0)
			{
				result.backtrackClassDef = bksge::make_unique<ClassDefinitionTable>(
					start + backtrackClassDefOffset);
			}
			if (inputClassDefOffset != 0)
			{
				result.inputClassDef = bksge::make_unique<ClassDefinitionTable>(
					start + inputClassDefOffset);
			}
			if (lookaheadClassDefOffset != 0)
			{
				result.lookaheadClassDef = bksge::make_unique<ClassDefinitionTable>(
					start + lookaheadClassDefOffset);
			}

			return result;
		}

		bksge::unique_ptr<CoverageTable>			coverage;
		bksge::unique_ptr<ClassDefinitionTable>		backtrackClassDef;
		bksge::unique_ptr<ClassDefinitionTable>		inputClassDef;
		bksge::unique_ptr<ClassDefinitionTable>		lookaheadClassDef;
		bksge::vector<ChainedClassSequenceRuleSet>	chainedClassSeqRuleSets;
	};

	struct Format3
	{
		static Format3 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format3 result;

			uint16		backtrackGlyphCount;
			uint16		inputGlyphCount;
			uint16		lookaheadGlyphCount;
			uint16		seqLookupCount;

			ptr = ReadBigEndian(ptr, &backtrackGlyphCount);
			for (uint16 i = 0; i < backtrackGlyphCount; ++i)
			{
				Offset16 backtrackCoverageOffset;
				ptr = ReadBigEndian(ptr, &backtrackCoverageOffset);
				result.backtrackCoverages.emplace_back(
					start + backtrackCoverageOffset);
			}

			ptr = ReadBigEndian(ptr, &inputGlyphCount);
			for (uint16 i = 0; i < inputGlyphCount; ++i)
			{
				Offset16 inputCoverageOffset;
				ptr = ReadBigEndian(ptr, &inputCoverageOffset);
				result.inputCoverages.emplace_back(
					start + inputCoverageOffset);
			}

			ptr = ReadBigEndian(ptr, &lookaheadGlyphCount);
			for (uint16 i = 0; i < lookaheadGlyphCount; ++i)
			{
				Offset16 lookaheadCoverageOffset;
				ptr = ReadBigEndian(ptr, &lookaheadCoverageOffset);
				result.lookaheadCoverages.emplace_back(
					start + lookaheadCoverageOffset);
			}

			ptr = ReadBigEndian(ptr, &seqLookupCount);
			result.seqLookupRecords.resize(seqLookupCount);
			ptr = ReadBigEndian(ptr, &result.seqLookupRecords);

			return result;
		}

		bksge::vector<CoverageTable>		backtrackCoverages;
		bksge::vector<CoverageTable>		inputCoverages;
		bksge::vector<CoverageTable>		lookaheadCoverages;
		bksge::vector<SequenceLookupRecord>	seqLookupRecords;
	};

	explicit ChainedSequenceContext(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16 format;
		ptr = ReadBigEndian(ptr, &format);
		switch (format)
		{
		case 1: value = Format1::Create(ptr, start); break;
		case 2: value = Format2::Create(ptr, start); break;
		case 3: value = Format3::Create(ptr, start); break;
		}
	}

	bksge::variant<
		Format1,
		Format2,
		Format3
	> value;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CHAINED_SEQUENCE_CONTEXT_HPP
