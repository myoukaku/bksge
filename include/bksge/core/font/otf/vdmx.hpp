/**
 *	@file	vdmx.hpp
 *
 *	@brief	VerticalDeviceMetrics の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_VDMX_HPP
#define BKSGE_CORE_FONT_OTF_VDMX_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct VerticalDeviceMetrics
{
	struct RatioRange
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, RatioRange* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->bCharSet);
			ptr = ReadBigEndian(ptr, &dst->xRatio);
			ptr = ReadBigEndian(ptr, &dst->yStartRatio);
			ptr = ReadBigEndian(ptr, &dst->yEndRatio);
			return ptr;
		}

		uint8	bCharSet;
		uint8	xRatio;
		uint8	yStartRatio;
		uint8	yEndRatio;
	};

	struct vTable
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, vTable* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->yPelHeight);
			ptr = ReadBigEndian(ptr, &dst->yMax);
			ptr = ReadBigEndian(ptr, &dst->yMin);
			return ptr;
		}

		uint16	yPelHeight;
		int16	yMax;
		int16	yMin;
	};

	struct VDMXGroup
	{
		explicit VDMXGroup(bksge::uint8_t const* ptr)
		{
			ptr = ReadBigEndian(ptr, &recs);
			ptr = ReadBigEndian(ptr, &startsz);
			ptr = ReadBigEndian(ptr, &endsz);
			entry.resize(recs);
			ptr = ReadBigEndian(ptr, &entry);
		}

		uint16					recs;
		uint8					startsz;
		uint8					endsz;
		bksge::vector<vTable>	entry;
	};

	explicit VerticalDeviceMetrics(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		version;
		uint16		numRecs;
		uint16		numRatios;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numRecs);
		ptr = ReadBigEndian(ptr, &numRatios);
		ratRange.resize(numRatios);
		ptr = ReadBigEndian(ptr, &ratRange);

		for (uint16 i = 0; i < numRatios; ++i)
		{
			Offset16 vdmxGroupOffset;
			ptr = ReadBigEndian(ptr, &vdmxGroupOffset);
			vdmxGroups.emplace_back(start + vdmxGroupOffset);
		}
	}

	bksge::vector<RatioRange>	ratRange;
	bksge::vector<VDMXGroup>	vdmxGroups;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_VDMX_HPP
