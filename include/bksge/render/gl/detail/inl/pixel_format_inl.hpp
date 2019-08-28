/**
 *	@file	pixel_format_inl.hpp
 *
 *	@brief	ToGlPixelFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/pixel_format.hpp>
#include <bksge/render/texture_format.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE ::GLenum
ToGlPixelFormat(bksge::TextureFormat format)
{
	static std::unordered_map<bksge::PixelSwizzle, ::GLenum> const m =
	{
		{ bksge::PixelSwizzle::kR,    GL_RED },
		{ bksge::PixelSwizzle::kRG,   GL_RG },
		{ bksge::PixelSwizzle::kRGB,  GL_RGB },
		{ bksge::PixelSwizzle::kBGR,  GL_BGR },
		{ bksge::PixelSwizzle::kRGBA, GL_RGBA },
		{ bksge::PixelSwizzle::kBGRA, GL_BGRA },
		{ bksge::PixelSwizzle::kARGB, GL_BGRA },
		{ bksge::PixelSwizzle::kABGR, GL_RGBA },
		{ bksge::PixelSwizzle::kDxt1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT },
		{ bksge::PixelSwizzle::kDxt3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT },
		{ bksge::PixelSwizzle::kDxt5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT },
	};

	return m.at(GetPixelSwizzle(format));
}

BKSGE_INLINE ::GLint
ToGlInternalPixelFormat(bksge::TextureFormat format)
{
	static std::unordered_map<bksge::PixelSwizzle, ::GLint> const m =
	{
		{ bksge::PixelSwizzle::kR,    GL_RED },
		{ bksge::PixelSwizzle::kRG,   GL_RG },
		{ bksge::PixelSwizzle::kRGB,  GL_RGB },
		{ bksge::PixelSwizzle::kBGR,  GL_RGB },
		{ bksge::PixelSwizzle::kRGBA, GL_RGBA },
		{ bksge::PixelSwizzle::kBGRA, GL_RGBA },
		{ bksge::PixelSwizzle::kARGB, GL_RGBA },
		{ bksge::PixelSwizzle::kABGR, GL_RGBA },
		{ bksge::PixelSwizzle::kDxt1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT },
		{ bksge::PixelSwizzle::kDxt3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT },
		{ bksge::PixelSwizzle::kDxt5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT },
	};

	return m.at(GetPixelSwizzle(format));
}

BKSGE_INLINE ::GLenum
ToGlPixelType(bksge::TextureFormat format)
{
	static std::unordered_map<bksge::PixelBaseFormat, ::GLenum> const m =
	{
		{ bksge::PixelBaseFormat::kU8,    GL_UNSIGNED_BYTE },
		{ bksge::PixelBaseFormat::kS8,    GL_BYTE },
		{ bksge::PixelBaseFormat::kU16,   GL_UNSIGNED_SHORT },
		{ bksge::PixelBaseFormat::kS16,   GL_SHORT },
		{ bksge::PixelBaseFormat::kU32,   GL_UNSIGNED_INT },
		{ bksge::PixelBaseFormat::kS32,   GL_INT },
		{ bksge::PixelBaseFormat::kF32,   GL_FLOAT },
		{ bksge::PixelBaseFormat::kDxt1,  GL_UNSIGNED_BYTE },
		{ bksge::PixelBaseFormat::kDxt35, GL_UNSIGNED_BYTE },
	};

	return m.at(GetPixelBaseFormat(format));
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP
