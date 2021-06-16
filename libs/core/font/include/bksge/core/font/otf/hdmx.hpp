/**
 *	@file	hdmx.hpp
 *
 *	@brief	HorizontalDeviceMetrics の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_HDMX_HPP
#define BKSGE_CORE_FONT_OTF_HDMX_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct HorizontalDeviceMetrics
{
	struct DeviceRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			DeviceRecord* dst,
			uint16 numGlyphs)
		{
			dst->widths.resize(numGlyphs);

			ptr = ReadBigEndian(ptr, &dst->pixelSize);
			ptr = ReadBigEndian(ptr, &dst->maxWidth);
			ptr = ReadBigEndian(ptr, &dst->widths);

			return ptr;
		}

		uint8					pixelSize;
		uint8					maxWidth;
		bksge::vector<uint8>	widths;
	};

	explicit HorizontalDeviceMetrics(bksge::uint8_t const* ptr, uint16 numGlyphs)
	{
		uint16	version;
		uint16	numRecords;
		uint32	sizeDeviceRecord;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numRecords);
		ptr = ReadBigEndian(ptr, &sizeDeviceRecord);
		records.resize(numRecords);
		ptr = ReadBigEndian(ptr, &records, numGlyphs);
	}

	bksge::vector<DeviceRecord>	records;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_HDMX_HPP
