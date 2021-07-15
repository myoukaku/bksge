/**
 *	@file	vvar.hpp
 *
 *	@brief	VerticalMetricsVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_VVAR_HPP
#define BKSGE_CORE_FONT_OTF_VVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/item_variation_store.hpp>
#include <bksge/core/font/otf/hvar.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct VerticalMetricsVariationsTable
{
	using DeltaSetIndexMap = HorizontalMetricsVariationsTable::DeltaSetIndexMap;

	explicit VerticalMetricsVariationsTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset32	itemVariationStoreOffset;
		Offset32	advanceHeightMappingOffset;
		Offset32	tsbMappingOffset;
		Offset32	bsbMappingOffset;
		Offset32	vOrgMappingOffset;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &itemVariationStoreOffset);
		ptr = ReadBigEndian(ptr, &advanceHeightMappingOffset);
		ptr = ReadBigEndian(ptr, &tsbMappingOffset);
		ptr = ReadBigEndian(ptr, &bsbMappingOffset);
		ptr = ReadBigEndian(ptr, &vOrgMappingOffset);

		if (itemVariationStoreOffset != 0)
		{
			itemVariationStore = bksge::make_unique<ItemVariationStore>(
				start + itemVariationStoreOffset);
		}
		if (advanceHeightMappingOffset != 0)
		{
			advanceHeightMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + advanceHeightMappingOffset);
		}
		if (tsbMappingOffset != 0)
		{
			tsbMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + tsbMappingOffset);
		}
		if (bsbMappingOffset != 0)
		{
			bsbMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + bsbMappingOffset);
		}
		if (vOrgMappingOffset != 0)
		{
			vOrgMapping = bksge::make_unique<DeltaSetIndexMap>(
				start + vOrgMappingOffset);
		}
	}

	bksge::unique_ptr<ItemVariationStore>	itemVariationStore;
	bksge::unique_ptr<DeltaSetIndexMap>		advanceHeightMapping;
	bksge::unique_ptr<DeltaSetIndexMap>		tsbMapping;
	bksge::unique_ptr<DeltaSetIndexMap>		bsbMapping;
	bksge::unique_ptr<DeltaSetIndexMap>		vOrgMapping;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_VVAR_HPP
