/**
 *	@file	descriptor_set_layout.hpp
 *
 *	@brief	DescriptorSetLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP

#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

struct DescriptorSetLayoutBinding : public ::VkDescriptorSetLayoutBinding
{
	DescriptorSetLayoutBinding(void);
};

struct DescriptorSetLayoutCreateInfo : public ::VkDescriptorSetLayoutCreateInfo
{
	DescriptorSetLayoutCreateInfo(void);
};

class DescriptorSetLayout
{
public:
	explicit DescriptorSetLayout(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorSetLayoutCreateInfo const& info,
		std::uint32_t num);

	~DescriptorSetLayout();

	::VkDescriptorSetLayout const* get(void) const;

private:
	std::vector<::VkDescriptorSetLayout>	m_descriptor_set_layout;
	std::shared_ptr<vk::Device>				m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_set_layout_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP
