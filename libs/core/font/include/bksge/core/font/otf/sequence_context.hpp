/**
 *	@file	sequence_context.hpp
 *
 *	@brief	SequenceContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_SEQUENCE_CONTEXT_HPP
#define BKSGE_CORE_FONT_OTF_SEQUENCE_CONTEXT_HPP

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

struct SequenceContext
{
	struct Format1
	{
		struct SequenceRule
		{
			explicit SequenceRule(std::uint8_t const* ptr)
			{
				uint16	glyphCount;
				uint16	seqLookupCount;

				ptr = ReadBigEndian(ptr, &glyphCount);
				ptr = ReadBigEndian(ptr, &seqLookupCount);
				inputSequence.resize(glyphCount - 1);
				ptr = ReadBigEndian(ptr, &inputSequence);
				seqLookupRecords.resize(seqLookupCount);
				ptr = ReadBigEndian(ptr, &seqLookupRecords);
			}

			bksge::vector<uint16>					inputSequence;
			bksge::vector<SequenceLookupRecord>		seqLookupRecords;
		};

		struct SequenceRuleSet
		{
			explicit SequenceRuleSet(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16 seqRuleCount;
				ptr = ReadBigEndian(ptr, &seqRuleCount);
				for (uint16 i = 0; i < seqRuleCount; ++i)
				{
					Offset16 seqRuleOffset;
					ptr = ReadBigEndian(ptr, &seqRuleOffset);
					seqRules.emplace_back(start + seqRuleOffset);
				}
			}

			bksge::vector<SequenceRule>		seqRules;
		};

		static Format1 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format1 result;

			Offset16	coverageOffset;
			uint16		seqRuleSetCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &seqRuleSetCount);
			for (uint16 i = 0; i < seqRuleSetCount; ++i)
			{
				Offset16 seqRuleSetOffset;
				ptr = ReadBigEndian(ptr, &seqRuleSetOffset);
				result.seqRuleSets.emplace_back(
					start + seqRuleSetOffset);
			}

			if (coverageOffset != 0)
			{
				result.coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}

			return result;
		}

		bksge::unique_ptr<CoverageTable>	coverage;
		bksge::vector<SequenceRuleSet>		seqRuleSets;
	};

	struct Format2
	{
		struct ClassSequenceRule
		{
			explicit ClassSequenceRule(std::uint8_t const* ptr)
			{
				uint16	glyphCount;
				uint16	seqLookupCount;
				ptr = ReadBigEndian(ptr, &glyphCount);
				ptr = ReadBigEndian(ptr, &seqLookupCount);
				inputSequence.resize(glyphCount - 1);
				ptr = ReadBigEndian(ptr, &inputSequence);
				seqLookupRecords.resize(seqLookupCount);
				ptr = ReadBigEndian(ptr, &seqLookupRecords);
			}

			bksge::vector<uint16>					inputSequence;
			bksge::vector<SequenceLookupRecord>		seqLookupRecords;
		};

		struct ClassSequenceRuleSet
		{
			explicit ClassSequenceRuleSet(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	classSeqRuleCount;
				ptr = ReadBigEndian(ptr, &classSeqRuleCount);
				for (uint16 i = 0; i < classSeqRuleCount; ++i)
				{
					Offset16 classSeqRuleOffset;
					ptr = ReadBigEndian(ptr, &classSeqRuleOffset);
					classSeqRules.emplace_back(start + classSeqRuleOffset);
				}
			}

			bksge::vector<ClassSequenceRule>		classSeqRules;
		};

		static Format2 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format2 result;

			Offset16	coverageOffset;
			Offset16	classDefOffset;
			uint16		classSeqRuleSetCount;

			ptr = ReadBigEndian(ptr, &coverageOffset);
			ptr = ReadBigEndian(ptr, &classDefOffset);
			ptr = ReadBigEndian(ptr, &classSeqRuleSetCount);
			for (uint16 i = 0; i < classSeqRuleSetCount; ++i)
			{
				Offset16 classSeqRuleSetOffset;
				ptr = ReadBigEndian(ptr, &classSeqRuleSetOffset);
				result.classSeqRuleSets.emplace_back(
					start + classSeqRuleSetOffset);
			}

			if (coverageOffset != 0)
			{
				result.coverage = bksge::make_unique<CoverageTable>(
					start + coverageOffset);
			}
			if (classDefOffset != 0)
			{
				result.classDef = bksge::make_unique<ClassDefinitionTable>(
					start + classDefOffset);
			}

			return result;
		}

		bksge::unique_ptr<CoverageTable>		coverage;
		bksge::unique_ptr<ClassDefinitionTable>	classDef;
		bksge::vector<ClassSequenceRuleSet>		classSeqRuleSets;
	};

	struct Format3
	{
		static Format3 Create(std::uint8_t const* ptr, std::uint8_t const* start)
		{
			Format3 result;

			uint16		glyphCount;
			uint16		seqLookupCount;
			ptr = ReadBigEndian(ptr, &glyphCount);
			ptr = ReadBigEndian(ptr, &seqLookupCount);

			for (uint16 i = 0; i < glyphCount; ++i)
			{
				Offset16 coverageOffset;
				ptr = ReadBigEndian(ptr, &coverageOffset);
				result.coverages.emplace_back(start + coverageOffset);
			}

			result.seqLookupRecords.resize(seqLookupCount);
			ptr = ReadBigEndian(ptr, &result.seqLookupRecords);

			return result;
		}

		bksge::vector<CoverageTable>			coverages;
		bksge::vector<SequenceLookupRecord>		seqLookupRecords;
	};

	explicit SequenceContext(std::uint8_t const* ptr)
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

#endif // BKSGE_CORE_FONT_OTF_SEQUENCE_CONTEXT_HPP
