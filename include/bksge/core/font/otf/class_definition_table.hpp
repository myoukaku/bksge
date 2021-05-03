/**
 *	@file	class_definition_table.hpp
 *
 *	@brief	ClassDefinitionTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CLASS_DEFINITION_TABLE_HPP
#define BKSGE_CORE_FONT_OTF_CLASS_DEFINITION_TABLE_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct ClassDefinitionTable
{
	struct ClassRangeRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, ClassRangeRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->startGlyphID);
			ptr = ReadBigEndian(ptr, &dst->endGlyphID);
			ptr = ReadBigEndian(ptr, &dst->klass);
			return ptr;
		}

		uint16	startGlyphID;
		uint16	endGlyphID;
		uint16	klass;
	};

	struct Format1
	{
		static Format1 Create(bksge::uint8_t const* ptr)
		{
			Format1 result;

			uint16	glyphCount;
			ptr = ReadBigEndian(ptr, &result.startGlyphID);
			ptr = ReadBigEndian(ptr, &glyphCount);
			result.classValueArray.resize(glyphCount);
			ptr = ReadBigEndian(ptr, &result.classValueArray);

			return result;
		}

		uint16					startGlyphID;
		bksge::vector<uint16>	classValueArray;
	};

	struct Format2
	{
		static Format2 Create(bksge::uint8_t const* ptr)
		{
			Format2 result;

			uint16	classRangeCount;
			ptr = ReadBigEndian(ptr, &classRangeCount);
			result.classRangeRecords.resize(classRangeCount);
			ptr = ReadBigEndian(ptr, &result.classRangeRecords);

			return result;
		}

		bksge::vector<ClassRangeRecord>	classRangeRecords;
	};

	explicit ClassDefinitionTable(bksge::uint8_t const* ptr)
	{
		uint16	classFormat;
		ptr = ReadBigEndian(ptr, &classFormat);
		switch (classFormat)
		{
		case 1: value = Format1::Create(ptr); break;
		case 2: value = Format2::Create(ptr); break;
		}
	}

	bksge::variant<
		Format1,
		Format2
	> value;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CLASS_DEFINITION_TABLE_HPP
