/**
 *	@file	feature_variations.hpp
 *
 *	@brief	FeatureVariations の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_FEATURE_VARIATIONS_HPP
#define BKSGE_CORE_FONT_OTF_FEATURE_VARIATIONS_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct FeatureVariations
{
	struct FeatureTableSubstitutionRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			FeatureTableSubstitutionRecord* dst,
			std::uint8_t const* start)
		{
			ptr = ReadBigEndian(ptr, &dst->featureIndex);
			ptr = ReadBigEndian(ptr, &dst->alternateFeatureOffset);

			if (dst->alternateFeatureOffset != 0)
			{
				// TODO
				//alternateFeature = bksge::make_unique<AlternateFeature>(
				//	start + alternateFeatureOffset);
				(void)start;
			}

			return ptr;
		}

		uint16		featureIndex;
		Offset32	alternateFeatureOffset;
	};

	struct FeatureTableSubstitution
	{
		explicit FeatureTableSubstitution(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	majorVersion;
			uint16	minorVersion;
			uint16	substitutionCount;

			ptr = ReadBigEndian(ptr, &majorVersion);
			ptr = ReadBigEndian(ptr, &minorVersion);
			ptr = ReadBigEndian(ptr, &substitutionCount);
			substitutions.resize(substitutionCount);
			ptr = ReadBigEndian(ptr, &substitutions, start);
		}

		bksge::vector<FeatureTableSubstitutionRecord>	substitutions;
	};

	struct Condition
	{
		explicit Condition(std::uint8_t const* ptr)
		{
			ptr = ReadBigEndian(ptr, &Format);
			ptr = ReadBigEndian(ptr, &AxisIndex);
			ptr = ReadBigEndian(ptr, &FilterRangeMinValue);
			ptr = ReadBigEndian(ptr, &FilterRangeMaxValue);
		}

		uint16	Format;
		uint16	AxisIndex;
		F2DOT14	FilterRangeMinValue;
		F2DOT14	FilterRangeMaxValue;
	};

	struct ConditionSet
	{
		explicit ConditionSet(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16 conditionCount;
			ptr = ReadBigEndian(ptr, &conditionCount);
			for (uint16 i = 0; i < conditionCount; ++i)
			{
				Offset32 conditionOffset;
				ptr = ReadBigEndian(ptr, &conditionOffset);
				conditions.emplace_back(start + conditionOffset);
			}
		}

		bksge::vector<Condition> conditions;
	};

	struct FeatureVariationRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			FeatureVariationRecord* dst,
			std::uint8_t const* start)
		{
			Offset32 conditionSetOffset;
			Offset32 featureTableSubstitutionOffset;

			ptr = ReadBigEndian(ptr, &conditionSetOffset);
			ptr = ReadBigEndian(ptr, &featureTableSubstitutionOffset);

			if (conditionSetOffset != 0)
			{
				dst->conditionSet =
					bksge::make_unique<ConditionSet>(
						start + conditionSetOffset);
			}
			if (featureTableSubstitutionOffset != 0)
			{
				dst->featureTableSubstitution =
					bksge::make_unique<FeatureTableSubstitution>(
						start + featureTableSubstitutionOffset);
			}

			return ptr;
		}

		bksge::unique_ptr<ConditionSet>				conditionSet;
		bksge::unique_ptr<FeatureTableSubstitution>	featureTableSubstitution;
	};

	explicit FeatureVariations(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16	majorVersion;
		uint16	minorVersion;
		uint32	featureVariationRecordCount;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &featureVariationRecordCount);
		featureVariationRecords.resize(featureVariationRecordCount);
		ptr = ReadBigEndian(ptr, &featureVariationRecords, start);
	}

	bksge::vector<FeatureVariationRecord>	featureVariationRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_FEATURE_VARIATIONS_HPP
