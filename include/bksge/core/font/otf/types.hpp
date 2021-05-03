/**
 *	@file	types.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_TYPES_HPP
#define BKSGE_CORE_FONT_OTF_TYPES_HPP

#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

using uint8	         = bksge::uint8_t;
using int8	         = bksge::int8_t;
using uint16         = bksge::uint16_t;
using int16          = bksge::int16_t;
using uint32         = bksge::uint32_t;
using int32	         = bksge::int32_t;
using Fixed	         = bksge::int32_t;
using FWORD	         = bksge::int16_t;
using UFWORD         = bksge::uint16_t;
using F2DOT14	     = bksge::int16_t;
using LONGDATETIME   = bksge::int64_t;
using Tag            = bksge::uint32_t;
using Offset16       = bksge::uint16_t;
using Offset32       = bksge::uint32_t;
using Version16Dot16 = bksge::uint32_t;

struct uint24
{
	bksge::uint8_t	value[3];

	operator uint32() const
	{
		bksge::uint32_t const a = value[0];
		bksge::uint32_t const b = value[1];
		bksge::uint32_t const c = value[2];
		return (a << 16) | (b << 8) | c;
	}
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_TYPES_HPP
