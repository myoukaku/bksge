/**
 *	@file	descriptor_pool.hpp
 *
 *	@brief	DescriptorPool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP

#include <bksge/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct DescriptorPoolCreateInfo : public ::VkDescriptorPoolCreateInfo
{
	DescriptorPoolCreateInfo(void);
};

class DescriptorPool
{
public:
	explicit DescriptorPool(
		std::shared_ptr<vk::Device> const& device,
		vk::DescriptorPoolCreateInfo const& info);

	~DescriptorPool();

	operator ::VkDescriptorPool() const;

private:
	::VkDescriptorPool			m_descriptor_pool;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/descriptor_pool_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_DESCRIPTOR_POOL_HPP
