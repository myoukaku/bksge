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
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <cstdint>
#include <vector>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct DescriptorSetAllocateInfo : public ::VkDescriptorSetAllocateInfo
{
	DescriptorSetAllocateInfo(void);
};

class DescriptorSet
{
public:
	explicit DescriptorSet(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorSetAllocateInfo const& info,
		std::uint32_t num);

	~DescriptorSet();

private:
	std::vector<::VkDescriptorSet>	m_descriptor_sets;
	std::shared_ptr<vk::Device>		m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_set_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
