/**
 *	@file	table_directory.hpp
 *
 *	@brief	TableDirectory の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_TABLE_DIRECTORY_HPP
#define BKSGE_CORE_FONT_OTF_TABLE_DIRECTORY_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct TableDirectory
{
	struct TableRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			TableRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->tableTag);
			ptr = ReadBigEndian(ptr, &dst->checksum);
			ptr = ReadBigEndian(ptr, &dst->offset);
			ptr = ReadBigEndian(ptr, &dst->length);
			return ptr;
		}

		Tag			tableTag;
		uint32		checksum;
		Offset32	offset;
		uint32		length;
	};

	explicit TableDirectory(bksge::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &sfntVersion);
		ptr = ReadBigEndian(ptr, &numTables);
		ptr = ReadBigEndian(ptr, &searchRange);
		ptr = ReadBigEndian(ptr, &entrySelector);
		ptr = ReadBigEndian(ptr, &rangeShift);

		tableRecords.resize(numTables);
		ptr = ReadBigEndian(ptr, &tableRecords);
	}

	uint32	sfntVersion;
	uint16	numTables;
	uint16	searchRange;
	uint16	entrySelector;
	uint16	rangeShift;
	bksge::vector<TableRecord> tableRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_TABLE_DIRECTORY_HPP
