/**
 *	@file	feature_list.hpp
 *
 *	@brief	FeatureList の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_FEATURE_LIST_HPP
#define BKSGE_CORE_FONT_OTF_FEATURE_LIST_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct FeatureList
{
	struct FeatureParams
	{
		explicit FeatureParams(bksge::uint8_t const* ptr)
		{
			// TODO
			(void)ptr;
		}
	};

	struct Feature
	{
		explicit Feature(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	featureParamsOffset;
			uint16		lookupIndexCount;

			ptr = ReadBigEndian(ptr, &featureParamsOffset);
			ptr = ReadBigEndian(ptr, &lookupIndexCount);
			lookupListIndices.resize(lookupIndexCount);
			ptr = ReadBigEndian(ptr, &lookupListIndices);

			if (featureParamsOffset != 0)
			{
				featureParams = bksge::make_unique<FeatureParams>(
					start + featureParamsOffset);
			}
		}

		bksge::unique_ptr<FeatureParams>	featureParams;
		bksge::vector<uint16>				lookupListIndices;
	};

	struct FeatureRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			FeatureRecord* dst,
			bksge::uint8_t const* start)
		{
			Offset16 featureOffset;

			ptr = ReadBigEndian(ptr, &dst->featureTag);
			ptr = ReadBigEndian(ptr, &featureOffset);

			if (featureOffset != 0)
			{
				dst->feature = bksge::make_unique<Feature>(
					start + featureOffset);
			}

			return ptr;
		}

		Tag							featureTag;
		bksge::unique_ptr<Feature>	feature;
	};

	explicit FeatureList(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16	featureCount;
		ptr = ReadBigEndian(ptr, &featureCount);
		featureRecords.resize(featureCount);
		ptr = ReadBigEndian(ptr, &featureRecords, start);
	}

	bksge::vector<FeatureRecord>	featureRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_FEATURE_LIST_HPP
