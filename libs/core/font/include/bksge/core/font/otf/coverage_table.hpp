/**
 *	@file	coverage_table.hpp
 *
 *	@brief	CoverageTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_COVERAGE_TABLE_HPP
#define BKSGE_CORE_FONT_OTF_COVERAGE_TABLE_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct CoverageTable
{
	struct RangeRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, RangeRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->startGlyphID);
			ptr = ReadBigEndian(ptr, &dst->endGlyphID);
			ptr = ReadBigEndian(ptr, &dst->startCoverageIndex);
			return ptr;
		}

		uint16	startGlyphID;
		uint16	endGlyphID;
		uint16	startCoverageIndex;
	};

	struct Format1
	{
		static Format1 Create(std::uint8_t const* ptr)
		{
			Format1 result;

			uint16	glyphCount;
			ptr = ReadBigEndian(ptr, &glyphCount);
			result.glyphArray.resize(glyphCount);
			ptr = ReadBigEndian(ptr, &result.glyphArray);

			return result;
		}

		bksge::vector<uint16>	glyphArray;
	};

	struct Format2
	{
		static Format2 Create(std::uint8_t const* ptr)
		{
			Format2 result;

			uint16	rangeCount;
			ptr = ReadBigEndian(ptr, &rangeCount);
			result.rangeRecords.resize(rangeCount);
			ptr = ReadBigEndian(ptr, &result.rangeRecords);

			return result;
		}

		bksge::vector<RangeRecord>	rangeRecords;
	};

	explicit CoverageTable(std::uint8_t const* ptr)
	{
		uint16	coverageFormat;
		ptr = ReadBigEndian(ptr, &coverageFormat);
		switch (coverageFormat)
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

#endif // BKSGE_CORE_FONT_OTF_COVERAGE_TABLE_HPP
