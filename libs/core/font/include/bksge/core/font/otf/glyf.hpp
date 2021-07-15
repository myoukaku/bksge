/**
 *	@file	glyf.hpp
 *
 *	@brief	GlyphData の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_GLYF_HPP
#define BKSGE_CORE_FONT_OTF_GLYF_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct GlyphData
{
	explicit GlyphData(std::uint8_t const* ptr, uint32 length)
		: m_buf(ptr, ptr + length)
	{}

	bksge::vector<uint8> m_buf;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_GLYF_HPP
