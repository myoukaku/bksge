/**
 *	@file	shader_stage_inl.hpp
 *
 *	@brief	ShaderStage の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_STAGE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_STAGE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/shader_stage.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader_stage.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkShaderStageFlagBits
ToVulkanShaderStage(bksge::ShaderStage shader_stage)
{
	switch (shader_stage)
	{
	case bksge::ShaderStage::kVertex:
		return VK_SHADER_STAGE_VERTEX_BIT;
	case bksge::ShaderStage::kGeometry:
		return VK_SHADER_STAGE_GEOMETRY_BIT;
	case bksge::ShaderStage::kFragment:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
	case bksge::ShaderStage::kTessellationControl:
		return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	case bksge::ShaderStage::kTessellationEvaluation:
		return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	}
	return VK_SHADER_STAGE_VERTEX_BIT;
}

}	// namespace detail

BKSGE_INLINE
ShaderStage::ShaderStage(bksge::ShaderStage shader_stage)
	: m_shader_stage(detail::ToVulkanShaderStage(shader_stage))
{}

BKSGE_INLINE
ShaderStage::operator ::VkShaderStageFlagBits() const
{
	return m_shader_stage;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_STAGE_INL_HPP
