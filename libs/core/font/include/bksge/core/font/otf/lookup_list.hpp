/**
 *	@file	lookup_list.hpp
 *
 *	@brief	LookupList の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_LOOKUP_LIST_HPP
#define BKSGE_CORE_FONT_OTF_LOOKUP_LIST_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/lookup.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct LookupList
{
	explicit LookupList(std::uint8_t const* ptr, Lookup::SubtableCreateFunc func)
	{
		auto const start = ptr;

		uint16 lookupCount;
		ptr = ReadBigEndian(ptr, &lookupCount);
		for (uint16 i = 0; i < lookupCount; ++i)
		{
			Offset16 lookupOffset;
			ptr = ReadBigEndian(ptr, &lookupOffset);
			lookups.emplace_back(start + lookupOffset, func);
		}
	}

	bksge::vector<Lookup>	lookups;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_LOOKUP_LIST_HPP
