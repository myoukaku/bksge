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
	switch (format)
	{
	case bksge::TextureFormat::kUndefined:
		return 0;

	case bksge::TextureFormat::kR_U8:
	case bksge::TextureFormat::kR_S8:
	case bksge::TextureFormat::kR_U8_NORM:
	case bksge::TextureFormat::kR_S8_NORM:
	case bksge::TextureFormat::kR_U16:
	case bksge::TextureFormat::kR_S16:
	case bksge::TextureFormat::kR_U16_NORM:
	case bksge::TextureFormat::kR_S16_NORM:
	case bksge::TextureFormat::kR_F16:
	case bksge::TextureFormat::kR_U32:
	case bksge::TextureFormat::kR_S32:
	case bksge::TextureFormat::kR_F32:
		return GL_RED;

	case bksge::TextureFormat::kRG_U8:
	case bksge::TextureFormat::kRG_S8:
	case bksge::TextureFormat::kRG_U8_NORM:
	case bksge::TextureFormat::kRG_S8_NORM:
	case bksge::TextureFormat::kRG_U16:
	case bksge::TextureFormat::kRG_S16:
	case bksge::TextureFormat::kRG_U16_NORM:
	case bksge::TextureFormat::kRG_S16_NORM:
	case bksge::TextureFormat::kRG_F16:
	case bksge::TextureFormat::kRG_U32:
	case bksge::TextureFormat::kRG_S32:
	case bksge::TextureFormat::kRG_F32:
		return GL_RG;

	case bksge::TextureFormat::kRGBA_U8:
	case bksge::TextureFormat::kRGBA_S8:
	case bksge::TextureFormat::kRGBA_U8_NORM:
	case bksge::TextureFormat::kRGBA_S8_NORM:
	case bksge::TextureFormat::kRGBA_U16:
	case bksge::TextureFormat::kRGBA_S16:
	case bksge::TextureFormat::kRGBA_U16_NORM:
	case bksge::TextureFormat::kRGBA_S16_NORM:
	case bksge::TextureFormat::kRGBA_F16:
	case bksge::TextureFormat::kRGBA_U32:
	case bksge::TextureFormat::kRGBA_S32:
	case bksge::TextureFormat::kRGBA_F32:
		return GL_RGBA;

	case bksge::TextureFormat::kDepth24_Stencil8:
		return GL_DEPTH_STENCIL;

	case bksge::TextureFormat::kBC1:
	case bksge::TextureFormat::kBC2:
	case bksge::TextureFormat::kBC3:
	case bksge::TextureFormat::kBC4:
	case bksge::TextureFormat::kBC5:
	case bksge::TextureFormat::kBC6H:
	case bksge::TextureFormat::kBC7:
		return GL_RGBA;
	}

	return 0;
}

BKSGE_INLINE ::GLint
ToGlInternalPixelFormat(bksge::TextureFormat format)
{
	switch (format)
	{
	case bksge::TextureFormat::kUndefined:		return 0;
	case bksge::TextureFormat::kR_U8:			return GL_R8UI;
	case bksge::TextureFormat::kR_S8:			return GL_R8I;
	case bksge::TextureFormat::kR_U8_NORM:		return GL_R8;
	case bksge::TextureFormat::kR_S8_NORM:		return GL_R8_SNORM;
	case bksge::TextureFormat::kR_U16:			return GL_R16UI;
	case bksge::TextureFormat::kR_S16:			return GL_R16I;
	case bksge::TextureFormat::kR_U16_NORM:		return GL_R16;
	case bksge::TextureFormat::kR_S16_NORM:		return GL_R16_SNORM;
	case bksge::TextureFormat::kR_F16:			return GL_R16F;
	case bksge::TextureFormat::kR_U32:			return GL_R32UI;
	case bksge::TextureFormat::kR_S32:			return GL_R32I;
	case bksge::TextureFormat::kR_F32:			return GL_R32F;
	case bksge::TextureFormat::kRG_U8:			return GL_RG8UI;
	case bksge::TextureFormat::kRG_S8:			return GL_RG8I;
	case bksge::TextureFormat::kRG_U8_NORM:		return GL_RG8;
	case bksge::TextureFormat::kRG_S8_NORM:		return GL_RG8_SNORM;
	case bksge::TextureFormat::kRG_U16:			return GL_RG16UI;
	case bksge::TextureFormat::kRG_S16:			return GL_RG16I;
	case bksge::TextureFormat::kRG_U16_NORM:	return GL_RG16;
	case bksge::TextureFormat::kRG_S16_NORM:	return GL_RG16_SNORM;
	case bksge::TextureFormat::kRG_F16:			return GL_RG16F;
	case bksge::TextureFormat::kRG_U32:			return GL_RG32UI;
	case bksge::TextureFormat::kRG_S32:			return GL_RG32I;
	case bksge::TextureFormat::kRG_F32:			return GL_RG32F;
	case bksge::TextureFormat::kRGBA_U8:		return GL_RGBA8UI;
	case bksge::TextureFormat::kRGBA_S8:		return GL_RGBA8I;
	case bksge::TextureFormat::kRGBA_U8_NORM:	return GL_RGBA8;
	case bksge::TextureFormat::kRGBA_S8_NORM:	return GL_RGBA8_SNORM;
	case bksge::TextureFormat::kRGBA_U16:		return GL_RGBA16UI;
	case bksge::TextureFormat::kRGBA_S16:		return GL_RGBA16I;
	case bksge::TextureFormat::kRGBA_U16_NORM:	return GL_RGBA16;
	case bksge::TextureFormat::kRGBA_S16_NORM:	return GL_RGBA16_SNORM;
	case bksge::TextureFormat::kRGBA_F16:		return GL_RGBA16F;
	case bksge::TextureFormat::kRGBA_U32:		return GL_RGBA32UI;
	case bksge::TextureFormat::kRGBA_S32:		return GL_RGBA32I;
	case bksge::TextureFormat::kRGBA_F32:		return GL_RGBA32F;
	case bksge::TextureFormat::kDepth24_Stencil8:	return GL_DEPTH_STENCIL;
	case bksge::TextureFormat::kBC1:  return GL_COMPRESSED_RGBA;
	case bksge::TextureFormat::kBC2:  return GL_COMPRESSED_RGBA;
	case bksge::TextureFormat::kBC3:  return GL_COMPRESSED_RGBA;
	case bksge::TextureFormat::kBC4:  return GL_COMPRESSED_RED_RGTC1;
	case bksge::TextureFormat::kBC5:  return GL_COMPRESSED_RG_RGTC2;
	case bksge::TextureFormat::kBC6H: return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
	case bksge::TextureFormat::kBC7:  return GL_COMPRESSED_RGBA_BPTC_UNORM;
	}

	return 0;
}

BKSGE_INLINE ::GLenum
ToGlPixelType(bksge::TextureFormat format)
{
	switch (format)
	{
	case bksge::TextureFormat::kUndefined:
		return 0;

	case bksge::TextureFormat::kR_U8:
	case bksge::TextureFormat::kRG_U8:
	case bksge::TextureFormat::kRGBA_U8:
	case bksge::TextureFormat::kR_U8_NORM:
	case bksge::TextureFormat::kRG_U8_NORM:
	case bksge::TextureFormat::kRGBA_U8_NORM:
		return GL_UNSIGNED_BYTE;

	case bksge::TextureFormat::kR_S8:
	case bksge::TextureFormat::kRG_S8:
	case bksge::TextureFormat::kRGBA_S8:
	case bksge::TextureFormat::kR_S8_NORM:
	case bksge::TextureFormat::kRG_S8_NORM:
	case bksge::TextureFormat::kRGBA_S8_NORM:
		return GL_BYTE;

	case bksge::TextureFormat::kR_U16:
	case bksge::TextureFormat::kRG_U16:
	case bksge::TextureFormat::kRGBA_U16:
	case bksge::TextureFormat::kR_U16_NORM:
	case bksge::TextureFormat::kRG_U16_NORM:
	case bksge::TextureFormat::kRGBA_U16_NORM:
		return GL_UNSIGNED_SHORT;

	case bksge::TextureFormat::kR_S16:
	case bksge::TextureFormat::kRG_S16:
	case bksge::TextureFormat::kRGBA_S16:
	case bksge::TextureFormat::kR_S16_NORM:
	case bksge::TextureFormat::kRG_S16_NORM:
	case bksge::TextureFormat::kRGBA_S16_NORM:
		return GL_SHORT;

	case bksge::TextureFormat::kR_F16:
	case bksge::TextureFormat::kRG_F16:
	case bksge::TextureFormat::kRGBA_F16:
		return GL_HALF_FLOAT;

	case bksge::TextureFormat::kR_U32:
	case bksge::TextureFormat::kRG_U32:
	case bksge::TextureFormat::kRGBA_U32:
		return GL_UNSIGNED_INT;

	case bksge::TextureFormat::kR_S32:
	case bksge::TextureFormat::kRG_S32:
	case bksge::TextureFormat::kRGBA_S32:
		return GL_INT;

	case bksge::TextureFormat::kR_F32:
	case bksge::TextureFormat::kRG_F32:
	case bksge::TextureFormat::kRGBA_F32:
		return GL_FLOAT;

	case bksge::TextureFormat::kDepth24_Stencil8:
		return GL_DEPTH24_STENCIL8;

	case bksge::TextureFormat::kBC1:
	case bksge::TextureFormat::kBC2:
	case bksge::TextureFormat::kBC3:
	case bksge::TextureFormat::kBC4:
	case bksge::TextureFormat::kBC5:
	case bksge::TextureFormat::kBC6H:
	case bksge::TextureFormat::kBC7:
		return GL_UNSIGNED_BYTE;
	}

	return 0;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_PIXEL_FORMAT_INL_HPP
