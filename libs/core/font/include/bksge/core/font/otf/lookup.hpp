/**
 *	@file	lookup.hpp
 *
 *	@brief	Lookup の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_LOOKUP_HPP
#define BKSGE_CORE_FONT_OTF_LOOKUP_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct Lookup
{
	struct Subtable
	{
		virtual ~Subtable() {}
	};

	using SubtableCreateFunc =
		bksge::unique_ptr<Subtable> (*)(uint16, std::uint8_t const*);

	explicit Lookup(std::uint8_t const* ptr, SubtableCreateFunc func)
	{
		auto const start = ptr;

		uint16	subTableCount;

		ptr = ReadBigEndian(ptr, &lookupType);
		ptr = ReadBigEndian(ptr, &lookupFlag);
		ptr = ReadBigEndian(ptr, &subTableCount);
		for (uint16 i = 0; i < subTableCount; ++i)
		{
			Offset16 subtableOffset;
			ptr = ReadBigEndian(ptr, &subtableOffset);
			subtables.emplace_back(
				func(lookupType, start + subtableOffset));
		}
		ptr = ReadBigEndian(ptr, &markFilteringSet);
	}

	using Subtables = bksge::vector<bksge::unique_ptr<Subtable>>;

	uint16			lookupType;
	uint16			lookupFlag;
	Subtables		subtables;
	uint16			markFilteringSet;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_LOOKUP_HPP
