/**
 *	@file	stat.hpp
 *
 *	@brief	StyleAttributesTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_STAT_HPP
#define BKSGE_CORE_FONT_OTF_STAT_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct StyleAttributesTable
{
	struct AxisValueTable
	{
		struct Format1
		{
			static Format1 Create(std::uint8_t const* ptr)
			{
				Format1 result;
				ptr = ReadBigEndian(ptr, &result.axisIndex);
				ptr = ReadBigEndian(ptr, &result.flags);
				ptr = ReadBigEndian(ptr, &result.valueNameID);
				ptr = ReadBigEndian(ptr, &result.value);
				return result;
			}

			uint16	axisIndex;
			uint16	flags;
			uint16	valueNameID;
			Fixed	value;
		};

		struct Format2
		{
			static Format2 Create(std::uint8_t const* ptr)
			{
				Format2 result;
				ptr = ReadBigEndian(ptr, &result.axisIndex);
				ptr = ReadBigEndian(ptr, &result.flags);
				ptr = ReadBigEndian(ptr, &result.valueNameID);
				ptr = ReadBigEndian(ptr, &result.nominalValue);
				ptr = ReadBigEndian(ptr, &result.rangeMinValue);
				ptr = ReadBigEndian(ptr, &result.rangeMaxValue);
				return result;
			}

			uint16	axisIndex;
			uint16	flags;
			uint16	valueNameID;
			Fixed	nominalValue;
			Fixed	rangeMinValue;
			Fixed	rangeMaxValue;
		};

		struct Format3
		{
			static Format3 Create(std::uint8_t const* ptr)
			{
				Format3 result;
				ptr = ReadBigEndian(ptr, &result.axisIndex);
				ptr = ReadBigEndian(ptr, &result.flags);
				ptr = ReadBigEndian(ptr, &result.valueNameID);
				ptr = ReadBigEndian(ptr, &result.value);
				ptr = ReadBigEndian(ptr, &result.linkedValue);
				return result;
			}

			uint16	axisIndex;
			uint16	flags;
			uint16	valueNameID;
			Fixed	value;
			Fixed	linkedValue;
		};

		struct Format4
		{
			struct AxisValue
			{
				friend std::uint8_t const*
				ReadBigEndian(std::uint8_t const* ptr, AxisValue* dst)
				{
					ptr = ReadBigEndian(ptr, &dst->axisIndex);
					ptr = ReadBigEndian(ptr, &dst->value);
					return ptr;
				}

				uint16	axisIndex;
				Fixed	value;
			};

			static Format4 Create(std::uint8_t const* ptr)
			{
				Format4 result;
				ptr = ReadBigEndian(ptr, &result.axisCount);
				ptr = ReadBigEndian(ptr, &result.flags);
				ptr = ReadBigEndian(ptr, &result.valueNameID);
				result.axisValues.resize(result.axisCount);
				ptr = ReadBigEndian(ptr, &result.axisValues);
				return result;
			}

			uint16						axisCount;
			uint16						flags;
			uint16						valueNameID;
			bksge::vector<AxisValue>	axisValues;
		};

		explicit AxisValueTable(std::uint8_t const* ptr)
		{
			uint16	format;
			ptr = ReadBigEndian(ptr, &format);
			switch (format)
			{
			case 1: value = Format1::Create(ptr); break;
			case 2: value = Format2::Create(ptr); break;
			case 3: value = Format3::Create(ptr); break;
			case 4: value = Format3::Create(ptr); break;
			}
		}

		bksge::variant<
			Format1,
			Format2,
			Format3,
			Format4
		> value;
	};

	struct AxisRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, AxisRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->axisTag);
			ptr = ReadBigEndian(ptr, &dst->axisNameID);
			ptr = ReadBigEndian(ptr, &dst->axisOrdering);
			return ptr;
		}

		Tag		axisTag;
		uint16	axisNameID;
		uint16	axisOrdering;
	};

	explicit StyleAttributesTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		uint16		designAxisSize;
		uint16		designAxisCount;
		Offset32	designAxesOffset;
		uint16		axisValueCount;
		Offset32	offsetToAxisValueOffsets;
		uint16		elidedFallbackNameID;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &designAxisSize);
		ptr = ReadBigEndian(ptr, &designAxisCount);
		ptr = ReadBigEndian(ptr, &designAxesOffset);
		ptr = ReadBigEndian(ptr, &axisValueCount);
		ptr = ReadBigEndian(ptr, &offsetToAxisValueOffsets);
		ptr = ReadBigEndian(ptr, &elidedFallbackNameID);

		ptr = start + designAxesOffset;
		designAxes.resize(designAxisCount);
		ptr = ReadBigEndian(ptr, &designAxes);

		ptr = start + offsetToAxisValueOffsets;
		for (uint16 i = 0; i < axisValueCount; ++i)
		{
			Offset16 axisValueOffset;
			ptr = ReadBigEndian(ptr, &axisValueOffset);
			axisValues.emplace_back(start + offsetToAxisValueOffsets + axisValueOffset);
		}
	}

	bksge::vector<AxisRecord>		designAxes;
	bksge::vector<AxisValueTable>	axisValues;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_STAT_HPP
