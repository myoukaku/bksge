/**
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
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_setter_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/combined_image_sampler_setter_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/vector.hpp>
#include <memory>
#include <string>

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

	bksge::vector<::VkPipelineShaderStageCreateInfo> const& GetStages(void) const;

	vulkan::DescriptorSetLayout const& GetDescriptorSetLayout(void) const;

	void LoadParameters(
		bksge::ShaderParameterMap const& shader_parameter_map,
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		vulkan::UniformBuffer* uniform_buffer,
		vulkan::ResourcePool* resource_pool);

	bksge::vector<::VkWriteDescriptorSet> GetWriteDescriptorSets(void) const;

private:
	void AddShaderStage(
		::VkShaderStageFlagBits stage,
		char const* name,
		bksge::vector<unsigned int> const& spv);

private:
	// noncopyable
	Shader(Shader const&) = delete;
	Shader& operator=(Shader const&) = delete;

private:
	vulkan::DeviceSharedPtr										m_device;
	bksge::vector<::VkPipelineShaderStageCreateInfo>			m_shader_stages;
	bksge::vector<vulkan::UniformBufferSetterUniquePtr>			m_uniform_buffer_setter;
	bksge::vector<vulkan::CombinedImageSamplerSetterUniquePtr>	m_combined_image_sampler_setter;
	vulkan::DescriptorSetLayoutUniquePtr						m_descriptor_set_layout;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_HPP
