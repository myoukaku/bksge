/**
 *	@file	spirv_cross.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SPIRV_CROSS_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SPIRV_CROSS_HPP

#include <spirv_glsl.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkShaderStageFlagBits ToVkShaderStage(spv::ExecutionModel model)
{
	switch (model)
	{
	case spv::ExecutionModelVertex:					return VK_SHADER_STAGE_VERTEX_BIT;
	case spv::ExecutionModelTessellationControl:	return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	case spv::ExecutionModelTessellationEvaluation:	return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
	case spv::ExecutionModelGeometry:				return VK_SHADER_STAGE_GEOMETRY_BIT;
	case spv::ExecutionModelFragment:				return VK_SHADER_STAGE_FRAGMENT_BIT;
	case spv::ExecutionModelGLCompute:				return VK_SHADER_STAGE_COMPUTE_BIT;
	default:
		return ::VkShaderStageFlagBits(0);	// TODO エラー処理
	}
}

}	// namespace detail

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SPIRV_CROSS_HPP
