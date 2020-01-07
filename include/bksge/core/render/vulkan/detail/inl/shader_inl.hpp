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
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
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
	for (auto const& info : reflection.GetUniformBuffers())
	{
		auto const& set     = info.set;
		auto const& binding = info.binding;

		m_uniform_buffer_map[set][binding] =
			bksge::make_unique<vulkan::UniformBuffer>(m_device, info);
	}

	m_descriptor_set = bksge::make_unique<vulkan::DescriptorSet>(
		m_device, reflection);

	// Update DescriptorSet
	{
		std::vector<::VkWriteDescriptorSet> writes;

		for (auto const& info : reflection.GetUniformBuffers())
		{
			auto const& set             = info.set;
			auto const& binding         = info.binding;
			//auto const& descriptor_type = info.descriptor_type;

			vk::WriteDescriptorSet write;
			write.dstSet           = m_descriptor_set->Get()[set];
			write.dstBinding       = binding;
			write.dstArrayElement  = 0;
			write.descriptorCount  = 1;
			write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;//descriptor_type; TODO
			write.pImageInfo       = nullptr;
			write.pBufferInfo      = m_uniform_buffer_map[set][binding]->GetDescriptorBufferInfo();
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

BKSGE_INLINE void
Shader::LoadParameters(bksge::ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& i : m_uniform_buffer_map)
	{
		for (auto&& j : i.second)
		{
			j.second->LoadParameters(shader_parameter_map);
		}
	}
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


#if 0
	for (auto const& resource : resources.uniform_buffers)
	{
		auto const spirv_type = glsl.get_type(resource.type_id);
		auto const base_type = spirv_type.basetype;
		auto const res_name = resource.name.c_str();
		auto const offset = glsl.get_decoration(resource.id, spv::DecorationOffset);
		auto const arraysize = spirv_type.array.empty() ? 0 : spirv_type.array[0];
		auto const bytesize = spirv_type.basetype == spirv_cross::SPIRType::Struct ? glsl.get_declared_struct_size(spirv_type) : 0;
		auto const descriptor_set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		auto const binding = glsl.get_decoration(resource.id, spv::DecorationBinding);
		auto const member_count = spirv_type.member_types.size();
		const char* BaseTypeName[] =
		{
			"Unknown",
			"Void",
			"Boolean",
			"SByte",
			"UByte",
			"Short",
			"UShort",
			"Int",
			"UInt",
			"Int64",
			"UInt64",
			"AtomicCounter",
			"Half",
			"Float",
			"Double",
			"Struct",
			"Image",
			"SampledImage",
			"Sampler",
			"AccelerationStructureNV",
		};

		printf("UniformBuffer\n");
		printf("name           :%s\n", res_name);
		printf("base_type      :%s\n", BaseTypeName[base_type]);
		printf("offset         :%u\n", offset);
		printf("arraysize      :%u\n", arraysize);
		printf("bytesize       :%zu\n", bytesize);
		printf("descriptor_set :%u\n", descriptor_set);
		printf("binding        :%u\n", binding);
		printf("member_count   :%zu\n", member_count);

		for (std::uint32_t index = 0; index < member_count; ++index)
		{
			auto const& member_type_id = spirv_type.member_types[index];

			auto const member_type      = glsl.get_type(member_type_id);
			auto const member_baseType  = member_type.basetype;
			auto const member_name      = glsl.get_member_name(resource.base_type_id, index).c_str();
			auto const member_bytesize  = glsl.get_declared_struct_member_size(spirv_type, index);
			auto const member_offset    = glsl.get_member_decoration(resource.base_type_id, index, spv::DecorationOffset);
			auto const member_arraysize = member_type.array.empty() ? 0 : member_type.array[0];

			printf("    member_name      :%s\n", member_name);
			printf("    member_baseType  :%s\n", BaseTypeName[member_baseType]);
			printf("    member_bytesize  :%zu\n", member_bytesize);
			printf("    member_offset    :%u\n", member_offset);
			printf("    member_arraysize :%u\n", member_arraysize);
			printf("\n");
		}
	}
#endif
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_INL_HPP
