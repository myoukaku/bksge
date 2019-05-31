/**
 *	@file	descriptor_pool.hpp
 *
 *	@brief	DescriptorPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct DescriptorPoolCreateInfo : public ::VkDescriptorPoolCreateInfo
{
	DescriptorPoolCreateInfo(void)
	{
		sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pNext         = nullptr;
		flags         = 0;
		maxSets       = 0;
		poolSizeCount = 0;
		pPoolSizes    = nullptr;
	}
};

class DescriptorPool
{
public:
	explicit DescriptorPool(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorPoolCreateInfo const& info)
		: m_descriptor_pool(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateDescriptorPool(*m_device, &info, nullptr, &m_descriptor_pool);
	}

	~DescriptorPool()
	{
		vk::DestroyDescriptorPool(*m_device, m_descriptor_pool, nullptr);
	}

	operator ::VkDescriptorPool() const
	{
		return m_descriptor_pool;
	}

private:
	::VkDescriptorPool			m_descriptor_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
