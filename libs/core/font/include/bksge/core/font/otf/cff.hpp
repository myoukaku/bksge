﻿/**
 *	@file	cff.hpp
 *
 *	@brief	CompactFontFormatTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CFF_HPP
#define BKSGE_CORE_FONT_OTF_CFF_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct CompactFontFormatTable
{
	explicit CompactFontFormatTable(bksge::uint8_t const* ptr, uint32 length)
		: m_buf(ptr, ptr + length)
	{}

	bksge::vector<uint8> m_buf;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CFF_HPP
