/**
 *	@file	vmtx.hpp
 *
 *	@brief	VerticalMetricsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_VMTX_HPP
#define BKSGE_CORE_FONT_OTF_VMTX_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct VerticalMetricsTable
{
	struct longVerMetric
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, longVerMetric* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->advanceHeight);
			ptr = ReadBigEndian(ptr, &dst->topSideBearing);
			return ptr;
		}

		uint16	advanceHeight;
		int16	topSideBearing;
	};

	explicit VerticalMetricsTable(
		std::uint8_t const* ptr,
		uint16	numOfLongVerMetrics,
		uint16	numGlyphs)
	{
		vMetrics.resize(numOfLongVerMetrics);
		ptr = ReadBigEndian(ptr, &vMetrics);

		topSideBearing.resize(numGlyphs - numOfLongVerMetrics);
		ptr = ReadBigEndian(ptr, &topSideBearing);
	}

	bksge::vector<longVerMetric>	vMetrics;
	bksge::vector<int16>			topSideBearing;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_VMTX_HPP
