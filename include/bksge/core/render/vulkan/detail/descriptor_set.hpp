/**
 *	@file	descriptor_set.hpp
 *
 *	@brief	DescriptorSet クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP

#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <vector>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorSet
{
public:
	explicit DescriptorSet(
		vulkan::DeviceSharedPtr const& device,
		vulkan::ShaderReflection const& reflection);

	~DescriptorSet();

	std::vector<::VkDescriptorSet> const& Get(void) const;

	vulkan::DescriptorSetLayout const& GetDescriptorSetLayout(void) const;

private:
	vulkan::DeviceSharedPtr					m_device;
	vulkan::DescriptorPoolUniquePtr			m_descriptor_pool;
	vulkan::DescriptorSetLayoutUniquePtr	m_descriptor_set_layout;
	std::vector<::VkDescriptorSet>			m_descriptor_sets;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_set_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
