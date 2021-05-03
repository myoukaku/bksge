/**
 *	@file	gasp.hpp
 *
 *	@brief	GaspTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GASP_HPP
#define BKSGE_CORE_FONT_OTF_GASP_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct GaspTable
{
	struct GaspRange
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, GaspRange* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->rangeMaxPPEM);
			ptr = ReadBigEndian(ptr, &dst->rangeGaspBehavior);
			return ptr;
		}

		uint16	rangeMaxPPEM;
		uint16	rangeGaspBehavior;
	};

	explicit GaspTable(bksge::uint8_t const* ptr)
	{
		uint16	version;
		uint16	numRanges;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numRanges);
		gaspRanges.resize(numRanges);
		ptr = ReadBigEndian(ptr, &gaspRanges);
	}

	bksge::vector<GaspRange>	gaspRanges;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_GASP_HPP
