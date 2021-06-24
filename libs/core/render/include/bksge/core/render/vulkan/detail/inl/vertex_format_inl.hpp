/**
 *	@file	vertex_format_inl.hpp
 *
 *	@brief	VertexFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_FORMAT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/vertex_format.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/detail/type_enum.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkFormat
ToVulkanVertexFormat(bksge::render::VertexAttribute const& attribute)
{
	auto const type = attribute.type();
	auto const num  = attribute.element_num();

	switch (type)
	{
	case bksge::TypeEnum::kSInt8:
		switch (num)
		{
		case 1: return VK_FORMAT_R8_SINT;
		case 2: return VK_FORMAT_R8G8_SINT;
		case 3: return VK_FORMAT_R8G8B8_SINT;
		case 4: return VK_FORMAT_R8G8B8A8_SINT;
		}
		break;
	case bksge::TypeEnum::kUInt8:
		switch (num)
		{
		case 1: return VK_FORMAT_R8_UINT;
		case 2: return VK_FORMAT_R8G8_UINT;
		case 3: return VK_FORMAT_R8G8B8_UINT;
		case 4: return VK_FORMAT_R8G8B8A8_UINT;
		}
		break;
	case bksge::TypeEnum::kSInt16:
		switch (num)
		{
		case 1: return VK_FORMAT_R16_SINT;
		case 2: return VK_FORMAT_R16G16_SINT;
		case 3: return VK_FORMAT_R16G16B16_SINT;
		case 4: return VK_FORMAT_R16G16B16A16_SINT;
		}
		break;
	case bksge::TypeEnum::kUInt16:
		switch (num)
		{
		case 1: return VK_FORMAT_R16_UINT;
		case 2: return VK_FORMAT_R16G16_UINT;
		case 3: return VK_FORMAT_R16G16B16_UINT;
		case 4: return VK_FORMAT_R16G16B16A16_UINT;
		}
		break;
	case bksge::TypeEnum::kSInt32:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_SINT;
		case 2: return VK_FORMAT_R32G32_SINT;
		case 3: return VK_FORMAT_R32G32B32_SINT;
		case 4: return VK_FORMAT_R32G32B32A32_SINT;
		}
		break;
	case bksge::TypeEnum::kUInt32:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_UINT;
		case 2: return VK_FORMAT_R32G32_UINT;
		case 3: return VK_FORMAT_R32G32B32_UINT;
		case 4: return VK_FORMAT_R32G32B32A32_UINT;
		}
		break;
	case bksge::TypeEnum::kFloat:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_SFLOAT;
		case 2: return VK_FORMAT_R32G32_SFLOAT;
		case 3: return VK_FORMAT_R32G32B32_SFLOAT;
		case 4: return VK_FORMAT_R32G32B32A32_SFLOAT;
		}
		break;
	}
	return VK_FORMAT_UNDEFINED;
}

}	// namespace detail

BKSGE_INLINE
VertexFormat::VertexFormat(
	bksge::render::VertexAttribute const& attribute)
	: m_format(detail::ToVulkanVertexFormat(attribute))
{}

BKSGE_INLINE
VertexFormat::operator ::VkFormat() const
{
	return m_format;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_FORMAT_INL_HPP
