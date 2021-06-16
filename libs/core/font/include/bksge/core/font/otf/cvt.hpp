/**
 *	@file	cvt.hpp
 *
 *	@brief	ControlValueTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CVT_HPP
#define BKSGE_CORE_FONT_OTF_CVT_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct ControlValueTable
{
	explicit ControlValueTable(bksge::uint8_t const* ptr, uint32 length)
	{
		uint32 const size = length / sizeof(FWORD);
		value.resize(size);
		ptr = ReadBigEndian(ptr, &value);
	}

	bksge::vector<FWORD> value;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CVT_HPP
