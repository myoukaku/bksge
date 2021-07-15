/**
 *	@file	tuple_variation_header.hpp
 *
 *	@brief	TupleVariationHeader の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_TUPLE_VARIATION_HEADER_HPP
#define BKSGE_CORE_FONT_OTF_TUPLE_VARIATION_HEADER_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/tuple_record.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct TupleVariationHeader
{
	enum TupleIndex : uint16
	{
		EMBEDDED_PEAK_TUPLE = 0x8000,
		INTERMEDIATE_REGION = 0x4000,
		PRIVATE_POINT_NUMBERS = 0x2000,
	};

	friend std::uint8_t const*
	ReadBigEndian(
		std::uint8_t const* ptr,
		TupleVariationHeader* dst,
		uint16 axisCount)
	{
		ptr = ReadBigEndian(ptr, &dst->variationDataSize);
		ptr = ReadBigEndian(ptr, &dst->tupleIndex);

		if (dst->tupleIndex & EMBEDDED_PEAK_TUPLE)
		{
			dst->peakTuple = bksge::make_unique<TupleRecord>();
			ptr = ReadBigEndian(ptr, dst->peakTuple.get(), axisCount);
		}

		if (dst->tupleIndex & INTERMEDIATE_REGION)
		{
			dst->intermediateStartTuple = bksge::make_unique<TupleRecord>();
			dst->intermediateEndTuple = bksge::make_unique<TupleRecord>();
			ptr = ReadBigEndian(ptr, dst->intermediateStartTuple.get(), axisCount);
			ptr = ReadBigEndian(ptr, dst->intermediateEndTuple.get(), axisCount);
		}

		return ptr;
	}

	uint16							variationDataSize;
	uint16							tupleIndex;
	bksge::unique_ptr<TupleRecord>	peakTuple;
	bksge::unique_ptr<TupleRecord>	intermediateStartTuple;
	bksge::unique_ptr<TupleRecord>	intermediateEndTuple;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_TUPLE_VARIATION_HEADER_HPP
