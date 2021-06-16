/**
 *	@file	ltsh.hpp
 *
 *	@brief	LinearThresholdTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_LTSH_HPP
#define BKSGE_CORE_FONT_OTF_LTSH_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct LinearThresholdTable
{
	explicit LinearThresholdTable(bksge::uint8_t const* ptr)
	{
		uint16	version;
		uint16	numGlyphs;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numGlyphs);
		yPels.resize(numGlyphs);
		ptr = ReadBigEndian(ptr, &yPels);
	}

	bksge::vector<uint8>	yPels;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_LTSH_HPP
