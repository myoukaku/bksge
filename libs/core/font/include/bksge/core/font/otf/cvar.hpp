/**
 *	@file	cvar.hpp
 *
 *	@brief	CVTVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CVAR_HPP
#define BKSGE_CORE_FONT_OTF_CVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/tuple_variation_header.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct CVTVariationsTable
{
	explicit CVTVariationsTable(std::uint8_t const* ptr, uint16 axisCount)
	{
		enum TupleVariationCount
		{
			SHARED_POINT_NUMBERS = 0x8000,
			COUNT_MASK = 0x0FFF,
		};

		uint16		majorVersion;
		uint16		minorVersion;
		uint16		tupleVariationCount;
		Offset16	dataOffset;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &tupleVariationCount);
		ptr = ReadBigEndian(ptr, &dataOffset);
		tupleVariationHeaders.resize(tupleVariationCount & COUNT_MASK);
		ptr = ReadBigEndian(ptr, &tupleVariationHeaders, axisCount);

		// TODO Serialized data
	}

	bksge::vector<TupleVariationHeader>	tupleVariationHeaders;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CVAR_HPP
