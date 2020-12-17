/**
 *	@file	pixel_format_inl.hpp
 *
 *	@brief	ToGlPixelFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/pixel_format.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE ::GLenum
ToGlPixelFormat(bksge::TextureFormat format)
{
	switch (GetPixelSwizzle(format))
	{
	case bksge::PixelSwizzle::kR:    return GL_RED;
	case bksge::PixelSwizzle::kRG:   return GL_RG;
	case bksge::PixelSwizzle::kRGB:  return GL_RGB;
	case bksge::PixelSwizzle::kBGR:  return GL_BGR;
	case bksge::PixelSwizzle::kRGBA: return GL_RGBA;
	case bksge::PixelSwizzle::kBGRA: return GL_BGRA;
	case bksge::PixelSwizzle::kARGB: return GL_BGRA;
	case bksge::PixelSwizzle::kABGR: return GL_RGBA;
	case bksge::PixelSwizzle::kDxt1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case bksge::PixelSwizzle::kDxt3: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case bksge::PixelSwizzle::kDxt5: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case bksge::PixelSwizzle::kNone: return 0;
	}

	return 0;
}

BKSGE_INLINE ::GLint
ToGlInternalPixelFormat(bksge::TextureFormat format)
{
	switch (GetPixelSwizzle(format))
	{
	case bksge::PixelSwizzle::kR:    return GL_RED;
	case bksge::PixelSwizzle::kRG:   return GL_RG;
	case bksge::PixelSwizzle::kRGB:  return GL_RGB;
	case bksge::PixelSwizzle::kBGR:  return GL_RGB;
	case bksge::PixelSwizzle::kRGBA: return GL_RGBA;
	case bksge::PixelSwizzle::kBGRA: return GL_RGBA;
	case bksge::PixelSwizzle::kARGB: return GL_RGBA;
	case bksge::PixelSwizzle::kABGR: return GL_RGBA;
	case bksge::PixelSwizzle::kDxt1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case bksge::PixelSwizzle::kDxt3: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case bksge::PixelSwizzle::kDxt5: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case bksge::PixelSwizzle::kNone: return 0;
	}

	return 0;
}

BKSGE_INLINE ::GLenum
ToGlPixelType(bksge::TextureFormat format)
{
	switch (GetPixelBaseFormat(format))
	{
	case bksge::PixelBaseFormat::kU8:    return GL_UNSIGNED_BYTE;
	case bksge::PixelBaseFormat::kS8:    return GL_BYTE;
	case bksge::PixelBaseFormat::kU16:   return GL_UNSIGNED_SHORT;
	case bksge::PixelBaseFormat::kS16:   return GL_SHORT;
	case bksge::PixelBaseFormat::kU32:   return GL_UNSIGNED_INT;
	case bksge::PixelBaseFormat::kS32:   return GL_INT;
	case bksge::PixelBaseFormat::kF32:   return GL_FLOAT;
	case bksge::PixelBaseFormat::kDxt1:  return GL_UNSIGNED_BYTE;
	case bksge::PixelBaseFormat::kDxt35: return GL_UNSIGNED_BYTE;
	case bksge::PixelBaseFormat::kNone:  return 0;
	}

	return 0;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP
