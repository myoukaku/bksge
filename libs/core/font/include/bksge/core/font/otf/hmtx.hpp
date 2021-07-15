/**
 *	@file	hmtx.hpp
 *
 *	@brief	HorizontalMetricsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_HMTX_HPP
#define BKSGE_CORE_FONT_OTF_HMTX_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct HorizontalMetricsTable
{
	struct longHorMetric
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, longHorMetric* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->advanceWidth);
			ptr = ReadBigEndian(ptr, &dst->lsb);
			return ptr;
		}

		uint16	advanceWidth;
		int16	lsb;
	};

	explicit HorizontalMetricsTable(
		std::uint8_t const* ptr,
		uint16	numberOfHMetrics,
		uint16	numGlyphs)
	{
		hMetrics.resize(numberOfHMetrics);
		ptr = ReadBigEndian(ptr, &hMetrics);

		uint16 const num_lsb = numGlyphs - numberOfHMetrics;
		leftSideBearings.resize(num_lsb);
		ptr = ReadBigEndian(ptr, &leftSideBearings);
	}

	bksge::vector<longHorMetric>	hMetrics;
	bksge::vector<int16>			leftSideBearings;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_HMTX_HPP
