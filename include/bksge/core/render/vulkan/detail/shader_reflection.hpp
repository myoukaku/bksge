﻿/**
 *	@file	shader_reflection.hpp
 *
 *	@brief	ShaderReflection クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP

#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace vulkan
{

struct ShaderReflectionUniformBuffer
{
	struct Member
	{
		std::string          name;
		std::size_t          bytes;
		std::uint32_t        offset;
	};

	std::uint32_t			set;
	std::uint32_t			binding;
	std::string				name;
	std::size_t				bytes;
	::VkShaderStageFlags	stage_flags;
	std::vector<Member>		members;
};

class ShaderReflection
{
public:
	explicit ShaderReflection(
		std::vector<std::vector<unsigned int>> const& spv_list);

	~ShaderReflection();

	std::uint32_t GetMaxSets(void) const;

	using UniformBuffers = std::vector<ShaderReflectionUniformBuffer>;

	UniformBuffers const& GetUniformBuffers(void) const;

private:
	std::uint32_t	m_max_sets = 0;
	UniformBuffers	m_uniform_buffers;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/shader_reflection_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP