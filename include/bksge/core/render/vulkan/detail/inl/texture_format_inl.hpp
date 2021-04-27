/**
 *	@file	texture_format_inl.hpp
 *
 *	@brief	TextureFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_FORMAT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/texture_format.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/texture_format.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkFormat
ToVulkanTextureFormat(bksge::TextureFormat texture_format)
{
	switch (texture_format)
	{
	case bksge::TextureFormat::kUndefined:			return VK_FORMAT_UNDEFINED;
	case bksge::TextureFormat::kR_U8:				return VK_FORMAT_R8_UINT;
	case bksge::TextureFormat::kR_S8:				return VK_FORMAT_R8_SINT;
	case bksge::TextureFormat::kR_U8_NORM:			return VK_FORMAT_R8_UNORM;
	case bksge::TextureFormat::kR_S8_NORM:			return VK_FORMAT_R8_SNORM;
	case bksge::TextureFormat::kR_U16:				return VK_FORMAT_R16_UINT;
	case bksge::TextureFormat::kR_S16:				return VK_FORMAT_R16_SINT;
	case bksge::TextureFormat::kR_U16_NORM:			return VK_FORMAT_R16_UNORM;
	case bksge::TextureFormat::kR_S16_NORM:			return VK_FORMAT_R16_SNORM;
	case bksge::TextureFormat::kR_F16:				return VK_FORMAT_R16_SFLOAT;
	case bksge::TextureFormat::kR_U32:				return VK_FORMAT_R32_UINT;
	case bksge::TextureFormat::kR_S32:				return VK_FORMAT_R32_SINT;
	case bksge::TextureFormat::kR_F32:				return VK_FORMAT_R32_SFLOAT;
	case bksge::TextureFormat::kRG_U8:				return VK_FORMAT_R8G8_UINT;
	case bksge::TextureFormat::kRG_S8:				return VK_FORMAT_R8G8_SINT;
	case bksge::TextureFormat::kRG_U8_NORM:			return VK_FORMAT_R8G8_UNORM;
	case bksge::TextureFormat::kRG_S8_NORM:			return VK_FORMAT_R8G8_SNORM;
	case bksge::TextureFormat::kRG_U16:				return VK_FORMAT_R16G16_UINT;
	case bksge::TextureFormat::kRG_S16:				return VK_FORMAT_R16G16_SINT;
	case bksge::TextureFormat::kRG_U16_NORM:		return VK_FORMAT_R16G16_UNORM;
	case bksge::TextureFormat::kRG_S16_NORM:		return VK_FORMAT_R16G16_SNORM;
	case bksge::TextureFormat::kRG_F16:				return VK_FORMAT_R16G16_SFLOAT;
	case bksge::TextureFormat::kRG_U32:				return VK_FORMAT_R32G32_UINT;
	case bksge::TextureFormat::kRG_S32:				return VK_FORMAT_R32G32_SINT;
	case bksge::TextureFormat::kRG_F32:				return VK_FORMAT_R32G32_SFLOAT;
	case bksge::TextureFormat::kRGBA_U8:			return VK_FORMAT_R8G8B8A8_UINT;
	case bksge::TextureFormat::kRGBA_S8:			return VK_FORMAT_R8G8B8A8_SINT;
	case bksge::TextureFormat::kRGBA_U8_NORM:		return VK_FORMAT_R8G8B8A8_UNORM;
	case bksge::TextureFormat::kRGBA_S8_NORM:		return VK_FORMAT_R8G8B8A8_SNORM;
	case bksge::TextureFormat::kRGBA_U16:			return VK_FORMAT_R16G16B16A16_UINT;
	case bksge::TextureFormat::kRGBA_S16:			return VK_FORMAT_R16G16B16A16_SINT;
	case bksge::TextureFormat::kRGBA_U16_NORM:		return VK_FORMAT_R16G16B16A16_UNORM;
	case bksge::TextureFormat::kRGBA_S16_NORM:		return VK_FORMAT_R16G16B16A16_SNORM;
	case bksge::TextureFormat::kRGBA_F16:			return VK_FORMAT_R16G16B16A16_SFLOAT;
	case bksge::TextureFormat::kRGBA_U32:			return VK_FORMAT_R32G32B32A32_UINT;
	case bksge::TextureFormat::kRGBA_S32:			return VK_FORMAT_R32G32B32A32_SINT;
	case bksge::TextureFormat::kRGBA_F32:			return VK_FORMAT_R32G32B32A32_SFLOAT;
	case bksge::TextureFormat::kDepth24_Stencil8:	return VK_FORMAT_D24_UNORM_S8_UINT;
	case bksge::TextureFormat::kBC1:				return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
	case bksge::TextureFormat::kBC2:				return VK_FORMAT_BC2_UNORM_BLOCK;
	case bksge::TextureFormat::kBC3:				return VK_FORMAT_BC3_UNORM_BLOCK;
	case bksge::TextureFormat::kBC4:				return VK_FORMAT_BC4_UNORM_BLOCK;
	case bksge::TextureFormat::kBC5:				return VK_FORMAT_BC5_UNORM_BLOCK;
	case bksge::TextureFormat::kBC6H:				return VK_FORMAT_BC6H_UFLOAT_BLOCK;
	case bksge::TextureFormat::kBC7:				return VK_FORMAT_BC7_UNORM_BLOCK;
	}
	return VK_FORMAT_UNDEFINED;
}

}	// namespace detail

BKSGE_INLINE
TextureFormat::TextureFormat(bksge::TextureFormat texture_format)
	: m_format(detail::ToVulkanTextureFormat(texture_format))
{}

BKSGE_INLINE
TextureFormat::operator VkFormat() const
{
	return m_format;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_FORMAT_INL_HPP
