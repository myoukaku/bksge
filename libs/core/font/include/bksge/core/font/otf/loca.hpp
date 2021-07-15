/**
 *	@file	loca.hpp
 *
 *	@brief	IndexToLocation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_LOCA_HPP
#define BKSGE_CORE_FONT_OTF_LOCA_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct IndexToLocation
{
	explicit IndexToLocation(
		std::uint8_t const* ptr,
		int16 indexToLocFormat,
		uint16 numGlyphs)
	{
		uint16 n = numGlyphs + 1;
		offsets.resize(n);

		if (indexToLocFormat == 0)
		{
			// Short version
			for (uint16 i = 0; i < n; ++i)
			{
				Offset16 offset;
				ptr = ReadBigEndian(ptr, &offset);
				offsets[i] = offset * 2;
			}
		}
		else
		{
			// Long version
			ptr = ReadBigEndian(ptr, &offsets);
		}
	}

	bksge::vector<Offset32>	offsets;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_LOCA_HPP
