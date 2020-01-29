/**
 *	@file	shader_reflection_inl.hpp
 *
 *	@brief	ShaderReflection クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_REFLECTION_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_REFLECTION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/spirv_cross.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline void AddUniformBuffer(
	spirv_cross::CompilerGLSL const& glsl,
	spirv_cross::SmallVector<spirv_cross::Resource> const& resource_vector,
	::VkShaderStageFlagBits stage,
	::VkDescriptorType descriptor_type,
	std::vector<ShaderReflectionUniform>* uniforms,
	std::uint32_t* max_sets)
{
	for (auto const& resource : resource_vector)
	{
		auto const spirv_type   = glsl.get_type(resource.type_id);
		auto const set          = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		auto const binding      = glsl.get_decoration(resource.id, spv::DecorationBinding);
		auto const name         = resource.name.c_str();
		auto const bytesize     = spirv_type.basetype == spirv_cross::SPIRType::Struct ? glsl.get_declared_struct_size(spirv_type) : 0;
		auto const member_count = spirv_type.member_types.size();

		*max_sets = bksge::max(*max_sets, set);

		auto it = std::find_if(
			uniforms->begin(),
			uniforms->end(),
			[=](ShaderReflectionUniform const& info)
			{
				return
					info.set == set &&
					info.binding == binding;
			});

		if (it != uniforms->end())
		{
			BKSGE_ASSERT(it->name == name);							// TODO assertじゃなくて続行可能なエラーにする
			BKSGE_ASSERT(it->descriptor_type == descriptor_type);	// TODO assertじゃなくて続行可能なエラーにする
			BKSGE_ASSERT(it->bytes == bytesize);					// TODO assertじゃなくて続行可能なエラーにする
			it->stage_flags |= stage;
		}
		else
		{
			ShaderReflectionUniform info;
			info.set             = set;
			info.binding         = binding;
			info.name            = name;
			info.descriptor_type = descriptor_type;
			info.bytes           = bytesize;
			info.stage_flags     = stage;
			info.members.resize(member_count);

			for (std::uint32_t index = 0; index < member_count; ++index)
			{
				auto& member = info.members[index];
				member.name   = glsl.get_member_name(resource.base_type_id, index);
				member.bytes  = glsl.get_declared_struct_member_size(spirv_type, index);
				member.offset = glsl.get_member_decoration(resource.base_type_id, index, spv::DecorationOffset);
			}

			uniforms->push_back(info);
		}
	}
}

}	// namespace detail

BKSGE_INLINE
ShaderReflection::ShaderReflection(
	std::vector<std::vector<unsigned int>> const& spv_list)
{
	for (auto&& spv : spv_list)
	{
		spirv_cross::CompilerGLSL glsl(spv);
		auto const stage = detail::ToVkShaderStage(glsl.get_execution_model());
		spirv_cross::ShaderResources resources = glsl.get_shader_resources();
		detail::AddUniformBuffer(glsl, resources.uniform_buffers, stage, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, &m_uniforms, &m_max_sets);
		detail::AddUniformBuffer(glsl, resources.sampled_images,  stage, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, &m_uniforms, &m_max_sets);
		//AddDescriptorSetInfo(glsl, resources.sampled_images,    stage, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, descriptor_set_info_list);
		//AddDescriptorSetInfo(glsl, resources.separate_images,   stage, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          descriptor_set_info_list);
		//AddDescriptorSetInfo(glsl, resources.separate_samplers, stage, VK_DESCRIPTOR_TYPE_SAMPLER,                descriptor_set_info_list);
	}

	std::sort(
		m_uniforms.begin(),
		m_uniforms.end(),
		[](ShaderReflectionUniform const& lhs,
		   ShaderReflectionUniform const& rhs)
		{
			return
				std::make_tuple(lhs.set, lhs.binding) <
				std::make_tuple(rhs.set, rhs.binding);
		}
	);
}

BKSGE_INLINE
ShaderReflection::~ShaderReflection()
{
}

BKSGE_INLINE std::uint32_t
ShaderReflection::GetMaxSets(void) const
{
	return m_max_sets;
}

BKSGE_INLINE std::uint32_t
ShaderReflection::GetUniformCount(::VkDescriptorType descriptor_type) const
{
	std::uint32_t result = 0;

	for (auto const& uniform : m_uniforms)
	{
		if (uniform.descriptor_type == descriptor_type)
		{
			++result;
		}
	}

	return result;
}

BKSGE_INLINE auto
ShaderReflection::GetUniforms(void) const
-> Uniforms const&
{
	return m_uniforms;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SHADER_REFLECTION_INL_HPP
