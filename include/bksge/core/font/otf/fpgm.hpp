/**
 *	@file	fpgm.hpp
 *
 *	@brief	FontProgram の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_FPGM_HPP
#define BKSGE_CORE_FONT_OTF_FPGM_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct FontProgram
{
	explicit FontProgram(bksge::uint8_t const* ptr, uint32 length)
	{
		value.resize(length);
		ptr = ReadBigEndian(ptr, &value);
	}

	bksge::vector<uint8> value;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_FPGM_HPP
