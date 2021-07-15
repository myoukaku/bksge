/**
 *	@file	merg.hpp
 *
 *	@brief	MergeTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_MERG_HPP
#define BKSGE_CORE_FONT_OTF_MERG_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/class_definition_table.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct MergeTable
{
	struct MergeEntryRow
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			MergeEntryRow* dst,
			uint16 mergeClassCount)
		{
			dst->mergeEntries.resize(mergeClassCount);
			ptr = ReadBigEndian(ptr, &dst->mergeEntries);
			return ptr;
		}

		bksge::vector<uint8>	mergeEntries;
	};

	struct MergeEntry
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			MergeEntry* dst,
			uint16 mergeClassCount)
		{
			dst->mergeEntryRows.resize(mergeClassCount);
			ptr = ReadBigEndian(ptr, &dst->mergeEntryRows, mergeClassCount);
			return ptr;
		}

		bksge::vector<MergeEntryRow>	mergeEntryRows;
	};

	explicit MergeTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		version;
		uint16		mergeClassCount;
		Offset16	mergeDataOffset;
		uint16		classDefCount;
		Offset16	offsetToClassDefOffsets;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &mergeClassCount);
		ptr = ReadBigEndian(ptr, &mergeDataOffset);
		ptr = ReadBigEndian(ptr, &classDefCount);
		ptr = ReadBigEndian(ptr, &offsetToClassDefOffsets);

		ReadBigEndian(start + mergeDataOffset, &mergeData, mergeClassCount);

		ptr = start + offsetToClassDefOffsets;
		for (uint16 i = 0; i < classDefCount; ++i)
		{
			Offset16 classDefOffset;
			ptr = ReadBigEndian(ptr, &classDefOffset);
			classDefTables.emplace_back(start + classDefOffset);
		}
	}

	MergeEntry							mergeData;
	bksge::vector<ClassDefinitionTable> classDefTables;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_MERG_HPP
