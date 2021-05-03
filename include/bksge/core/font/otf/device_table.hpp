/**
 *	@file	device_table.hpp
 *
 *	@brief	DeviceTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_DEVICE_TABLE_HPP
#define BKSGE_CORE_FONT_OTF_DEVICE_TABLE_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/variant.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct DeviceTable
{
	enum DeltaFormat : uint16
	{
		LOCAL_2_BIT_DELTAS = 0x0001,
		LOCAL_4_BIT_DELTAS = 0x0002,
		LOCAL_8_BIT_DELTAS = 0x0003,
		VARIATION_INDEX    = 0x8000,
	};

	struct Device
	{
		static Device Create(
			bksge::uint8_t const* ptr,
			uint16 value1,
			uint16 value2,
			uint16 deltaFormat)
		{
			Device result;

			result.startSize = value1;
			result.endSize   = value2;

			uint16 const deltaValueCount =
				result.endSize - result.startSize + 1;
			switch (deltaFormat)
			{
			case LOCAL_2_BIT_DELTAS:
				for (;;)
				{
					int8 deltaValue;
					ptr = ReadBigEndian(ptr, &deltaValue);

					// first 2 bits as signed integer
					result.deltaValues.push_back(deltaValue >> 6);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}

					// second 2 bits as signed integer
					result.deltaValues.push_back((deltaValue << 2) >> 6);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}

					// third 2 bits as signed integer
					result.deltaValues.push_back((deltaValue << 4) >> 6);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}

					// fourth 2 bits as signed integer
					result.deltaValues.push_back((deltaValue << 6) >> 6);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}
				}
				break;
			case LOCAL_4_BIT_DELTAS:
				for (;;)
				{
					int8 deltaValue;
					ptr = ReadBigEndian(ptr, &deltaValue);

					// first 4 bits as signed integer
					result.deltaValues.push_back(deltaValue >> 4);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}

					// second 4 bits as signed integer
					result.deltaValues.push_back((deltaValue << 4) >> 4);
					if (result.deltaValues.size() >= deltaValueCount)
					{
						break;
					}
				}
				break;
			case LOCAL_8_BIT_DELTAS:
				result.deltaValues.resize(deltaValueCount);
				ptr = ReadBigEndian(ptr, &result.deltaValues);
				break;
			}

			return result;
		}

		uint16					startSize;
		uint16					endSize;
		bksge::vector<int8>		deltaValues;
	};

	struct VariationIndex
	{
		static VariationIndex Create(uint16 value1, uint16 value2)
		{
			VariationIndex result;
			result.deltaSetOuterIndex = value1;
			result.deltaSetInnerIndex = value2;
			return result;
		}

		uint16	deltaSetOuterIndex;
		uint16	deltaSetInnerIndex;
	};

	explicit DeviceTable(bksge::uint8_t const* ptr)
	{
		uint16	value1;
		uint16	value2;
		uint16	deltaFormat;
		ptr = ReadBigEndian(ptr, &value1);
		ptr = ReadBigEndian(ptr, &value2);
		ptr = ReadBigEndian(ptr, &deltaFormat);
		if (deltaFormat == VARIATION_INDEX)
		{
			value = VariationIndex::Create(value1, value2);
		}
		else
		{
			value = Device::Create(ptr, value1, value2, deltaFormat);
		}
	}

	bksge::variant<
		Device,
		VariationIndex
	> value;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_DEVICE_TABLE_HPP
