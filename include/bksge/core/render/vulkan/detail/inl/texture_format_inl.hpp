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
	case bksge::TextureFormat::kR_U8:		return VK_FORMAT_R8_UNORM;
	case bksge::TextureFormat::kR_S8:		return VK_FORMAT_R8_SNORM;
	case bksge::TextureFormat::kR_U16:		return VK_FORMAT_R16_UNORM;
	case bksge::TextureFormat::kR_S16:		return VK_FORMAT_R16_SNORM;
	case bksge::TextureFormat::kR_U32:		return VK_FORMAT_R32_UINT;
	case bksge::TextureFormat::kR_S32:		return VK_FORMAT_R32_SINT;
	case bksge::TextureFormat::kR_F32:		return VK_FORMAT_R32_SFLOAT;
	case bksge::TextureFormat::kRG_U8:		return VK_FORMAT_R8G8_UNORM;
	case bksge::TextureFormat::kRG_S8:		return VK_FORMAT_R8G8_SNORM;
	case bksge::TextureFormat::kRG_U16:		return VK_FORMAT_R16G16_UNORM;
	case bksge::TextureFormat::kRG_S16:		return VK_FORMAT_R16G16_SNORM;
	case bksge::TextureFormat::kRG_U32:		return VK_FORMAT_R32G32_UINT;
	case bksge::TextureFormat::kRG_S32:		return VK_FORMAT_R32G32_SINT;
	case bksge::TextureFormat::kRG_F32:		return VK_FORMAT_R32G32_SFLOAT;
	case bksge::TextureFormat::kRGB_U8:		return VK_FORMAT_R8G8B8_UNORM;
	case bksge::TextureFormat::kRGB_S8:		return VK_FORMAT_R8G8B8_SNORM;
	case bksge::TextureFormat::kRGB_U16:	return VK_FORMAT_R16G16B16_UNORM;
	case bksge::TextureFormat::kRGB_S16:	return VK_FORMAT_R16G16B16_SNORM;
	case bksge::TextureFormat::kRGB_U32:	return VK_FORMAT_R32G32B32_UINT;
	case bksge::TextureFormat::kRGB_S32:	return VK_FORMAT_R32G32B32_SINT;
	case bksge::TextureFormat::kRGB_F32:	return VK_FORMAT_R32G32B32_SFLOAT;
	//case bksge::TextureFormat::kBGR_U8:		return ;
	//case bksge::TextureFormat::kBGR_S8:		return ;
	//case bksge::TextureFormat::kBGR_U16:	return ;
	//case bksge::TextureFormat::kBGR_S16:	return ;
	//case bksge::TextureFormat::kBGR_U32:	return ;
	//case bksge::TextureFormat::kBGR_S32:	return ;
	//case bksge::TextureFormat::kBGR_F32:	return ;
	case bksge::TextureFormat::kRGBA_U8:	return VK_FORMAT_R8G8B8A8_UNORM;
	case bksge::TextureFormat::kRGBA_S8:	return VK_FORMAT_R8G8B8A8_SNORM;
	case bksge::TextureFormat::kRGBA_U16:	return VK_FORMAT_R16G16B16A16_UNORM;
	case bksge::TextureFormat::kRGBA_S16:	return VK_FORMAT_R16G16B16A16_SNORM;
	case bksge::TextureFormat::kRGBA_U32:	return VK_FORMAT_R32G32B32A32_UINT;
	case bksge::TextureFormat::kRGBA_S32:	return VK_FORMAT_R32G32B32A32_SINT;
	case bksge::TextureFormat::kRGBA_F32:	return VK_FORMAT_R32G32B32A32_SFLOAT;
	case bksge::TextureFormat::kBGRA_U8:	return VK_FORMAT_B8G8R8A8_UNORM;
	case bksge::TextureFormat::kBGRA_S8:	return VK_FORMAT_B8G8R8A8_SNORM;
	//case bksge::TextureFormat::kBGRA_U16:	return ;
	//case bksge::TextureFormat::kBGRA_S16:	return ;
	//case bksge::TextureFormat::kBGRA_U32:	return ;
	//case bksge::TextureFormat::kBGRA_S32:	return ;
	//case bksge::TextureFormat::kBGRA_F32:	return ;
	//case bksge::TextureFormat::kARGB_U8:	return ;
	//case bksge::TextureFormat::kARGB_S8:	return ;
	//case bksge::TextureFormat::kARGB_U16:	return ;
	//case bksge::TextureFormat::kARGB_S16:	return ;
	//case bksge::TextureFormat::kARGB_U32:	return ;
	//case bksge::TextureFormat::kARGB_S32:	return ;
	//case bksge::TextureFormat::kARGB_F32:	return ;
	//case bksge::TextureFormat::kABGR_U8:	return ;
	//case bksge::TextureFormat::kABGR_S8:	return ;
	//case bksge::TextureFormat::kABGR_U16:	return ;
	//case bksge::TextureFormat::kABGR_S16:	return ;
	//case bksge::TextureFormat::kABGR_U32:	return ;
	//case bksge::TextureFormat::kABGR_S32:	return ;
	//case bksge::TextureFormat::kABGR_F32:	return ;
	//case bksge::TextureFormat::kDxt1:		return ;
	//case bksge::TextureFormat::kDxt3:		return ;
	//case bksge::TextureFormat::kDxt5:		return ;
	default:
		return VK_FORMAT_UNDEFINED;
	}
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
