/**
 *	@file	descriptor_set.hpp
 *
 *	@brief	DescriptorSet クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
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
	DescriptorSetAllocateInfo(void)
	{
		sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		pNext              = nullptr;
		descriptorPool     = VK_NULL_HANDLE;
		descriptorSetCount = 0;
		pSetLayouts        = nullptr;
	}
};

class DescriptorSet
{
public:
	explicit DescriptorSet(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorSetAllocateInfo const& info,
		std::uint32_t num)
		: m_device(device)
	{
		m_descriptor_sets.resize(num);
		vk::AllocateDescriptorSets(*m_device, &info, m_descriptor_sets.data());
	}

	~DescriptorSet()
	{
//		vk::FreeDescriptorSets(*m_device, *m_descriptor_pool, m_descriptor_sets.size(), m_descriptor_sets.data());
	}

private:
	std::vector<::VkDescriptorSet>	m_descriptor_sets;
	std::shared_ptr<vk::Device>		m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
