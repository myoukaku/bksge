/**
 *	@file	uniform_buffer.hpp
 *
 *	@brief	UniformBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class UniformBuffer
{
public:
	explicit UniformBuffer(
		vulkan::DeviceSharedPtr const& device,
		vulkan::ShaderReflectionUniformBuffer const& reflection);

	~UniformBuffer();

	void LoadParameters(bksge::ShaderParameterMap const& shader_parameter_map);

	::VkDescriptorBufferInfo const* GetDescriptorBufferInfo(void) const;

private:
	struct Variable
	{
		std::string		name;
		std::size_t		bytes;
		std::uint32_t	offset;
	};

	vulkan::DeviceSharedPtr			m_device;
	vulkan::BufferUniquePtr			m_buffer;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
	::VkDescriptorBufferInfo		m_descriptor_buffer_info;
	std::string						m_name;
	std::size_t						m_bytes = 0;
	std::vector<Variable>			m_variables;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/uniform_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
