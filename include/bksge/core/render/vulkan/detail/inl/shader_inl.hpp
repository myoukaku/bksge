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
#include <bksge/core/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_set.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer_setter.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/glsl_to_spv.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/assert.hpp>
#include <memory>
#include <string>
#include <vector>
#include "spirv_glsl.hpp"

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

// TODO 重複
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
	}
	return ::VkShaderStageFlagBits(0);	// TODO エラー処理
}

}	// namespace detail

BKSGE_INLINE
Shader::Shader(
	vulkan::DeviceSharedPtr const& device,
	bksge::Shader const& shader,
	vulkan::UniformBuffer* uniform_buffer)
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
	for (auto const& info : reflection.GetUniformBuffers())
	{
		m_uniform_buffer_setter.push_back(
			bksge::make_unique<vulkan::UniformBufferSetter>(info));
	}

	m_descriptor_set = bksge::make_unique<vulkan::DescriptorSet>(
		m_device, reflection);

	::VkDescriptorBufferInfo buffer_info;
	buffer_info.buffer = *(uniform_buffer->GetBuffer());
	buffer_info.offset = 0;
	buffer_info.range  = VK_WHOLE_SIZE;

	// Update DescriptorSet
	{
		std::vector<::VkWriteDescriptorSet> writes;

		for (auto const& info : reflection.GetUniformBuffers())
		{
			auto const& set             = info.set;
			auto const& binding         = info.binding;

			vk::WriteDescriptorSet write;
			write.dstSet           = m_descriptor_set->Get()[set];
			write.dstBinding       = binding;
			write.dstArrayElement  = 0;
			write.descriptorCount  = 1;
			write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			write.pImageInfo       = nullptr;
			write.pBufferInfo      = &buffer_info;
			//write.pTexelBufferView = nullptr;

			writes.push_back(write);
		}

		vk::UpdateDescriptorSets(
			*m_device,
			static_cast<std::uint32_t>(writes.size()),
			writes.data(),
			0,
			nullptr);
	}
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
	return m_descriptor_set->GetDescriptorSetLayout();
}

BKSGE_INLINE std::unique_ptr<vulkan::DescriptorSet> const&
Shader::GetDescriptorSet(void) const
{
	return m_descriptor_set;
}

BKSGE_INLINE std::vector<std::uint32_t>
Shader::LoadParameters(
	bksge::ShaderParameterMap const& shader_parameter_map,
	vulkan::UniformBuffer* uniform_buffer)
{
	std::vector<std::uint32_t> offsets;

	for (auto&& setter : m_uniform_buffer_setter)
	{
		offsets.push_back(static_cast<std::uint32_t>(
			setter->LoadParameters(shader_parameter_map, uniform_buffer)));
	}

	return offsets;
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

	vk::CreateShaderModule(*m_device, &module_create_info, nullptr, &shader_stage_create_info.module);

	m_shader_stages.push_back(shader_stage_create_info);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_INL_HPP
