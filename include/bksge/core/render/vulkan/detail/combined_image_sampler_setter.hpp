/**
 *	@file	combined_image_sampler_setter.hpp
 *
 *	@brief	CombinedImageSamplerSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_SETTER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_SETTER_HPP

#include <bksge/core/render/vulkan/detail/fwd/combined_image_sampler_setter_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <cstddef>
#include <cstdint>
#include <string>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CombinedImageSamplerSetter
{
public:
	explicit CombinedImageSamplerSetter(
		vulkan::ShaderReflectionUniform const& reflection);

	~CombinedImageSamplerSetter();

	void LoadParameters(
		bksge::ShaderParameterMap const& shader_parameter_map,
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		vulkan::UniformBuffer* uniform_buffer,
		vulkan::ResourcePool* resource_pool);

	vk::WriteDescriptorSet GetWriteDescriptorSet(void) const;

private:
	// noncopyable
	CombinedImageSamplerSetter(CombinedImageSamplerSetter const&) = delete;
	CombinedImageSamplerSetter& operator=(CombinedImageSamplerSetter const&) = delete;

private:
	std::uint32_t					m_set = 0;
	std::uint32_t					m_binding = 0;
	std::string						m_name;
	::VkDescriptorType				m_descriptor_type;
	::VkDescriptorImageInfo			m_image_info;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/combined_image_sampler_setter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_SETTER_HPP
