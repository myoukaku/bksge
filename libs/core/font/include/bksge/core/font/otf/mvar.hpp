/**
 *	@file	mvar.hpp
 *
 *	@brief	MetricsVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_MVAR_HPP
#define BKSGE_CORE_FONT_OTF_MVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/item_variation_store.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct MetricsVariationsTable
{
	struct ValueRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(std::uint8_t const* ptr, ValueRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->valueTag);
			ptr = ReadBigEndian(ptr, &dst->deltaSetOuterIndex);
			ptr = ReadBigEndian(ptr, &dst->deltaSetInnerIndex);
			return ptr;
		}

		Tag		valueTag;
		uint16	deltaSetOuterIndex;
		uint16	deltaSetInnerIndex;
	};

	explicit MetricsVariationsTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		uint16		reserved;
		uint16		valueRecordSize;
		uint16		valueRecordCount;
		Offset16	itemVariationStoreOffset;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &reserved);
		ptr = ReadBigEndian(ptr, &valueRecordSize);
		ptr = ReadBigEndian(ptr, &valueRecordCount);
		ptr = ReadBigEndian(ptr, &itemVariationStoreOffset);
		valueRecords.resize(valueRecordCount);
		ptr = ReadBigEndian(ptr, &valueRecords);

		if (itemVariationStoreOffset != 0)
		{
			itemVariationStore = bksge::make_unique<ItemVariationStore>(
				start + itemVariationStoreOffset);
		}
	}

	bksge::unique_ptr<ItemVariationStore>	itemVariationStore;
	bksge::vector<ValueRecord>				valueRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_MVAR_HPP
