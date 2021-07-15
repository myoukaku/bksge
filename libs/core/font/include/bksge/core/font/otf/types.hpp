/**
 *	@file	types.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_TYPES_HPP
#define BKSGE_CORE_FONT_OTF_TYPES_HPP

#include <cstdint>

namespace bksge
{

namespace otf
{

using uint8	         = std::uint8_t;
using int8	         = std::int8_t;
using uint16         = std::uint16_t;
using int16          = std::int16_t;
using uint32         = std::uint32_t;
using int32	         = std::int32_t;
using Fixed	         = std::int32_t;
using FWORD	         = std::int16_t;
using UFWORD         = std::uint16_t;
using F2DOT14	     = std::int16_t;
using LONGDATETIME   = std::int64_t;
using Tag            = std::uint32_t;
using Offset16       = std::uint16_t;
using Offset32       = std::uint32_t;
using Version16Dot16 = std::uint32_t;

struct uint24
{
	std::uint8_t	value[3];

	operator uint32() const
	{
		std::uint32_t const a = value[0];
		std::uint32_t const b = value[1];
		std::uint32_t const c = value[2];
		return (a << 16) | (b << 8) | c;
	}
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_TYPES_HPP
