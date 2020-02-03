/**
 *	@file	shader_inl.hpp
 *
 *	@brief	Shader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/shader_stage.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/vulkan/detail/spirv_h.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer_setter.hpp>
#include <bksge/core/render/vulkan/detail/combined_image_sampler_setter.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/glsl_to_spv.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/spirv_cross.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/assert.hpp>
#include <memory>
#include <string>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Shader::Shader(
	vulkan::DeviceSharedPtr const& device,
	bksge::Shader const& shader)
	: m_device(device)
{
	// Create Spv List
	std::vector<std::vector<unsigned int>> spv_list;

	for (auto&& it : shader)
	{
		auto const& stage  = it.first;
		auto const& source = it.second;

		::VkShaderStageFlagBits const vk_stage = vulkan::ShaderStage(stage);

		auto spv = GlslToSpv(vk_stage, source.c_str());
		spv_list.push_back(std::move(spv));
	}

	// Create ShaderStages
	for (auto&& spv : spv_list)
	{
		spirv_cross::CompilerGLSL glsl(spv);
		auto const stage = detail::ToVkShaderStage(glsl.get_execution_model());
		AddShaderStage(stage, "main", spv);
	}

	ShaderReflection reflection(spv_list);

	// Create UniformBuffers
	for (auto const& info : reflection.GetUniforms())
	{
		switch (info.descriptor_type)
		{
		case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
			m_uniform_buffer_setter.push_back(
				bksge::make_unique<vulkan::UniformBufferSetter>(info));
			break;
		case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
			m_combined_image_sampler_setter.push_back(
				bksge::make_unique<vulkan::CombinedImageSamplerSetter>(info));
			break;
		default:
			// TODO
			break;
		}
	}

	m_descriptor_set_layout =
		bksge::make_unique<vulkan::DescriptorSetLayout>(m_device, reflection);
}

BKSGE_INLINE
Shader::~Shader()
{
	for (auto&& shader_stage : m_shader_stages)
	{
		vk::DestroyShaderModule(*m_device, shader_stage.module, nullptr);
	}
}

BKSGE_INLINE std::vector<::VkPipelineShaderStageCreateInfo> const&
Shader::GetStages(void) const
{
	return m_shader_stages;
}

BKSGE_INLINE vulkan::DescriptorSetLayout const&
Shader::GetDescriptorSetLayout(void) const
{
	return *m_descriptor_set_layout;
}

BKSGE_INLINE void
Shader::LoadParameters(
	bksge::ShaderParameterMap const& shader_parameter_map,
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	vulkan::UniformBuffer* uniform_buffer,
	vulkan::ResourcePool* resource_pool)
{
	for (auto&& setter : m_uniform_buffer_setter)
	{
		setter->LoadParameters(shader_parameter_map, uniform_buffer);
	}
	for (auto&& setter : m_combined_image_sampler_setter)
	{
		setter->LoadParameters(
			shader_parameter_map,
			device,
			command_pool,
			uniform_buffer,
			resource_pool);
	}
}

BKSGE_INLINE std::vector<::VkWriteDescriptorSet>
Shader::GetWriteDescriptorSets(void) const
{
	std::vector<::VkWriteDescriptorSet> writes;

	for (auto&& setter : m_uniform_buffer_setter)
	{
		writes.push_back(
			setter->GetWriteDescriptorSet());
	}
	for (auto&& setter : m_combined_image_sampler_setter)
	{
		writes.push_back(
			setter->GetWriteDescriptorSet());
	}

	return writes;
}

BKSGE_INLINE void
Shader::AddShaderStage(
	::VkShaderStageFlagBits stage,
	char const* name,
	std::vector<unsigned int> const& spv)
{
	vk::PipelineShaderStageCreateInfo shader_stage_create_info;
	shader_stage_create_info.stage               = stage;
	shader_stage_create_info.module              = VK_NULL_HANDLE;
	shader_stage_create_info.pName               = name;
	shader_stage_create_info.pSpecializationInfo = nullptr;

	vk::ShaderModuleCreateInfo module_create_info;
	module_create_info.codeSize = spv.size() * sizeof(unsigned int);
	module_create_info.pCode    = spv.data();

	vk::CreateShaderModule(
		*m_device,
		&module_create_info,
		nullptr,
		&shader_stage_create_info.module);

	m_shader_stages.push_back(shader_stage_create_info);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_INL_HPP
