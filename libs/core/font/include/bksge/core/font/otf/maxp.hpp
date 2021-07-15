/**
 *	@file	maxp.hpp
 *
 *	@brief	MaximumProfile の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_MAXP_HPP
#define BKSGE_CORE_FONT_OTF_MAXP_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct MaximumProfile
{
	explicit MaximumProfile(std::uint8_t const* ptr)
	{
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numGlyphs);
		if (version == 0x00005000)
		{
			return;
		}
		ptr = ReadBigEndian(ptr, &maxPoints);
		ptr = ReadBigEndian(ptr, &maxContours);
		ptr = ReadBigEndian(ptr, &maxCompositePoints);
		ptr = ReadBigEndian(ptr, &maxCompositeContours);
		ptr = ReadBigEndian(ptr, &maxZones);
		ptr = ReadBigEndian(ptr, &maxTwilightPoints);
		ptr = ReadBigEndian(ptr, &maxStorage);
		ptr = ReadBigEndian(ptr, &maxFunctionDefs);
		ptr = ReadBigEndian(ptr, &maxInstructionDefs);
		ptr = ReadBigEndian(ptr, &maxStackElements);
		ptr = ReadBigEndian(ptr, &maxSizeOfInstructions);
		ptr = ReadBigEndian(ptr, &maxComponentElements);
		ptr = ReadBigEndian(ptr, &maxComponentDepth);
	}

	// Version 0.5
	Version16Dot16	version;
	uint16	numGlyphs = 0;
	// Version 1.0
	uint16	maxPoints = 0;
	uint16	maxContours = 0;
	uint16	maxCompositePoints = 0;
	uint16	maxCompositeContours = 0;
	uint16	maxZones = 0;
	uint16	maxTwilightPoints = 0;
	uint16	maxStorage = 0;
	uint16	maxFunctionDefs = 0;
	uint16	maxInstructionDefs = 0;
	uint16	maxStackElements = 0;
	uint16	maxSizeOfInstructions = 0;
	uint16	maxComponentElements = 0;
	uint16	maxComponentDepth = 0;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_MAXP_HPP
