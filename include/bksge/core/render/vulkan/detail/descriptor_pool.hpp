/**
 *	@file	descriptor_pool.hpp
 *
 *	@brief	DescriptorPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP

#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorPool
{
public:
	explicit DescriptorPool(
		vulkan::DeviceSharedPtr const& device,
		vulkan::ShaderReflection const& reflection);

	~DescriptorPool();

	void AllocateDescriptorSets(
		std::vector<::VkDescriptorSetLayout> const& descriptor_set_layouts,
		VkDescriptorSet*                            descriptor_sets);

	void FreeDescriptorSets(
		std::vector<::VkDescriptorSet> const& descriptor_sets);

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkDescriptorPool			m_descriptor_pool;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
