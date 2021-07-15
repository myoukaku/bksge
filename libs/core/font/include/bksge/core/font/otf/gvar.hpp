/**
 *	@file	gvar.hpp
 *
 *	@brief	GlyphVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GVAR_HPP
#define BKSGE_CORE_FONT_OTF_GVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/tuple_record.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct GlyphVariationsTable
{
	struct GlyphVariationData
	{
		explicit GlyphVariationData(
			std::uint8_t const* ptr,
			uint16 axisCount)
		{
			enum TupleVariationCount
			{
				SHARED_POINT_NUMBERS = 0x8000,
				COUNT_MASK = 0x0FFF,
			};

			uint16		tupleVariationCount;
			Offset16	dataOffset;

			ptr = ReadBigEndian(ptr, &tupleVariationCount);
			ptr = ReadBigEndian(ptr, &dataOffset);
			tupleVariationHeaders.resize(tupleVariationCount & COUNT_MASK);
			ptr = ReadBigEndian(ptr, &tupleVariationHeaders, axisCount);

			// TODO Serialized data
		}

		bksge::vector<TupleVariationHeader>	tupleVariationHeaders;
	};

	struct SharedTuples
	{
		explicit SharedTuples(
			std::uint8_t const* ptr,
			uint16 axisCount,
			uint16 sharedTupleCount)
		{
			sharedTuples.resize(sharedTupleCount);
			ptr = ReadBigEndian(ptr, &sharedTuples, axisCount);
		}

		bksge::vector<TupleRecord>	sharedTuples;
	};

	explicit GlyphVariationsTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		uint16		axisCount;
		uint16		sharedTupleCount;
		Offset32	sharedTuplesOffset;
		uint16		glyphCount;
		uint16		flags;
		Offset32	glyphVariationDataArrayOffset;
		//Offset16 or Offset32	glyphVariationDataOffsets[glyphCount + 1];

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &axisCount);
		ptr = ReadBigEndian(ptr, &sharedTupleCount);
		ptr = ReadBigEndian(ptr, &sharedTuplesOffset);
		ptr = ReadBigEndian(ptr, &glyphCount);
		ptr = ReadBigEndian(ptr, &flags);
		ptr = ReadBigEndian(ptr, &glyphVariationDataArrayOffset);

		sharedTuples = bksge::make_unique<SharedTuples>(
			start + sharedTuplesOffset, axisCount, sharedTupleCount);

		// TODO glyphVariationDataArray
	}

	bksge::unique_ptr<SharedTuples>	sharedTuples;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_GVAR_HPP
