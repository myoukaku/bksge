/**
 *	@file	texture_format_fwd.hpp
 *
 *	@brief	TextureFormat の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_TEXTURE_FORMAT_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_TEXTURE_FORMAT_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class TextureFormat : bksge::uint32_t;
enum class PixelSwizzle : bksge::uint32_t;
enum class PixelBaseFormat : bksge::uint32_t;

}	// namespace render

using render::TextureFormat;
using render::PixelSwizzle;
using render::PixelBaseFormat;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_TEXTURE_FORMAT_FWD_HPP
