/**
 *	@file	descriptor_set_layout.hpp
 *
 *	@brief	DescriptorSetLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct DescriptorSetLayoutBinding : public ::VkDescriptorSetLayoutBinding
{
	DescriptorSetLayoutBinding(void)
	{
		binding            = 0;
		descriptorType     = VK_DESCRIPTOR_TYPE_SAMPLER;
		descriptorCount    = 0;
		stageFlags         = 0;
		pImmutableSamplers = nullptr;
	}
};

struct DescriptorSetLayoutCreateInfo : public ::VkDescriptorSetLayoutCreateInfo
{
	DescriptorSetLayoutCreateInfo(void)
	{
		sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		pNext        = nullptr;
		flags        = 0;
		bindingCount = 0;
		pBindings    = nullptr;
	}
};

class DescriptorSetLayout
{
public:
	explicit DescriptorSetLayout(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorSetLayoutCreateInfo const& info,
		std::uint32_t num)
		: m_device(device)
	{
		m_descriptor_set_layout.resize(num);
		vk::CreateDescriptorSetLayout(*m_device, &info, nullptr, m_descriptor_set_layout.data());
	}

	~DescriptorSetLayout()
	{
		for (auto&& layout : m_descriptor_set_layout)
		{
			vk::DestroyDescriptorSetLayout(*m_device, layout, nullptr);
		}
	}

	::VkDescriptorSetLayout const* get(void) const
	{
		return m_descriptor_set_layout.data();
	}

private:
	std::vector<::VkDescriptorSetLayout>	m_descriptor_set_layout;
	std::shared_ptr<vk::Device>				m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP
