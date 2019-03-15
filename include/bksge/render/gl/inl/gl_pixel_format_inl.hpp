/**
 *	@file	gl_pixel_format_inl.hpp
 *
 *	@brief	ToGlPixelFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_PIXEL_FORMAT_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_PIXEL_FORMAT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_pixel_format.hpp>
#include <bksge/render/texture_format.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlPixelFormat(TextureFormat format)
{
	static std::unordered_map<PixelSwizzle, GLenum> const m =
	{
		{ PixelSwizzle::kR,    GL_RED },
		{ PixelSwizzle::kRG,   GL_RG },
		{ PixelSwizzle::kRGB,  GL_RGB },
		{ PixelSwizzle::kBGR,  GL_BGR },
		{ PixelSwizzle::kRGBA, GL_RGBA },
		{ PixelSwizzle::kBGRA, GL_BGRA },
		{ PixelSwizzle::kARGB, GL_BGRA },
		{ PixelSwizzle::kABGR, GL_RGBA },
		{ PixelSwizzle::kDxt1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT },
		{ PixelSwizzle::kDxt3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT },
		{ PixelSwizzle::kDxt5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT },
	};

	return m.at(GetPixelSwizzle(format));
}

BKSGE_INLINE
GLint ToGlInternalPixelFormat(TextureFormat format)
{
	static std::unordered_map<PixelSwizzle, GLint> const m =
	{
		{ PixelSwizzle::kR,    GL_RED },
		{ PixelSwizzle::kRG,   GL_RG },
		{ PixelSwizzle::kRGB,  GL_RGB },
		{ PixelSwizzle::kBGR,  GL_RGB },
		{ PixelSwizzle::kRGBA, GL_RGBA },
		{ PixelSwizzle::kBGRA, GL_RGBA },
		{ PixelSwizzle::kARGB, GL_RGBA },
		{ PixelSwizzle::kABGR, GL_RGBA },
		{ PixelSwizzle::kDxt1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT },
		{ PixelSwizzle::kDxt3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT },
		{ PixelSwizzle::kDxt5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT },
	};

	return m.at(GetPixelSwizzle(format));
}

BKSGE_INLINE
GLenum ToGlPixelType(TextureFormat format)
{
	static std::unordered_map<PixelBaseFormat, GLenum> const m =
	{
		{ PixelBaseFormat::kU8,    GL_UNSIGNED_BYTE },
		{ PixelBaseFormat::kS8,    GL_BYTE },
		{ PixelBaseFormat::kU16,   GL_UNSIGNED_SHORT },
		{ PixelBaseFormat::kS16,   GL_SHORT },
		{ PixelBaseFormat::kU32,   GL_UNSIGNED_INT },
		{ PixelBaseFormat::kS32,   GL_INT },
		{ PixelBaseFormat::kF32,   GL_FLOAT },
		{ PixelBaseFormat::kDxt1,  GL_UNSIGNED_BYTE },
		{ PixelBaseFormat::kDxt35, GL_UNSIGNED_BYTE },
	};

	return m.at(GetPixelBaseFormat(format));
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_PIXEL_FORMAT_INL_HPP
