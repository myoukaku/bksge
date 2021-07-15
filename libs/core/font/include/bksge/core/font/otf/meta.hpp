/**
 *	@file	meta.hpp
 *
 *	@brief	MetadataTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_META_HPP
#define BKSGE_CORE_FONT_OTF_META_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct MetadataTable
{
	struct DataMap
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			DataMap* dst,
			std::uint8_t const* start)
		{
			Offset32	dataOffset;
			uint32		dataLength;
			ptr = ReadBigEndian(ptr, &dst->tag);
			ptr = ReadBigEndian(ptr, &dataOffset);
			ptr = ReadBigEndian(ptr, &dataLength);
			dst->data.resize(dataLength);
			ReadBigEndian(start + dataOffset, &dst->data);
			return ptr;
		}

		Tag						tag;
		bksge::vector<uint8>	data;
	};

	explicit MetadataTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint32	version;
		uint32	flags;
		uint32	reserved;
		uint32	dataMapsCount;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &flags);
		ptr = ReadBigEndian(ptr, &reserved);
		ptr = ReadBigEndian(ptr, &dataMapsCount);
		dataMaps.resize(dataMapsCount);
		ptr = ReadBigEndian(ptr, &dataMaps, start);
	}

	bksge::vector<DataMap>	dataMaps;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_META_HPP
