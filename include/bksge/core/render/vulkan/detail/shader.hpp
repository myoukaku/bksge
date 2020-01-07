﻿/**
 *	@file	shader.hpp
 *
 *	@brief	Shader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_HPP

#include <bksge/core/render/vulkan/detail/fwd/shader_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Shader
{
public:
	explicit Shader(
		vulkan::DeviceSharedPtr const& device,
		bksge::Shader const& shader);

	~Shader();

	std::vector<::VkPipelineShaderStageCreateInfo> const& GetStages(void) const;

	vulkan::DescriptorSetLayout const& GetDescriptorSetLayout(void) const;

	std::unique_ptr<vulkan::DescriptorSet> const& GetDescriptorSet(void) const;

	void LoadParameters(bksge::ShaderParameterMap const& shader_parameter_map);

private:
	void AddShaderStage(
		::VkShaderStageFlagBits stage,
		char const* name,
		std::vector<unsigned int> const& spv);

private:
	vulkan::DeviceSharedPtr						m_device;
	std::vector<::VkPipelineShaderStageCreateInfo>		m_shader_stages;
	std::map<std::uint32_t, std::map<std::uint32_t, std::unique_ptr<vulkan::UniformBuffer>>>	m_uniform_buffer_map;
	vulkan::DescriptorSetUniquePtr				m_descriptor_set;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_HPP
