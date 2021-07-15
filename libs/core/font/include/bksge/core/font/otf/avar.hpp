/**
 *	@file	avar.hpp
 *
 *	@brief	AxisVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_AVAR_HPP
#define BKSGE_CORE_FONT_OTF_AVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct AxisVariationsTable
{
	struct AxisValueMap
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, AxisValueMap* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->fromCoordinate);
			ptr = ReadBigEndian(ptr, &dst->toCoordinate);
			return ptr;
		}

		F2DOT14	fromCoordinate;
		F2DOT14	toCoordinate;
	};

	struct SegmentMaps
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, SegmentMaps* dst)
		{
			uint16	positionMapCount;
			ptr = ReadBigEndian(ptr, &positionMapCount);
			dst->axisValueMaps.resize(positionMapCount);
			ptr = ReadBigEndian(ptr, &dst->axisValueMaps);
			return ptr;
		}

		bksge::vector<AxisValueMap>	axisValueMaps;
	};

	explicit AxisVariationsTable(std::uint8_t const* ptr)
	{
		uint16	majorVersion;
		uint16	minorVersion;
		uint16	reserved;
		uint16	axisCount;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &reserved);
		ptr = ReadBigEndian(ptr, &axisCount);
		axisSegmentMaps.resize(axisCount);
		ptr = ReadBigEndian(ptr, &axisSegmentMaps);
	}

	bksge::vector<SegmentMaps>	axisSegmentMaps;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_AVAR_HPP
