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
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorSetLayout
{
public:
	explicit DescriptorSetLayout(
		vulkan::DeviceSharedPtr const& device,
		vulkan::ShaderReflection const& reflection);

	~DescriptorSetLayout();

	bksge::vector<::VkDescriptorSetLayout> const& GetLayouts(void) const;

private:
	// noncopyable
	DescriptorSetLayout(DescriptorSetLayout const&) = delete;
	DescriptorSetLayout& operator=(DescriptorSetLayout const&) = delete;

private:
	vulkan::DeviceSharedPtr					m_device;
	bksge::vector<::VkDescriptorSetLayout>	m_descriptor_set_layout;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_set_layout_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_LAYOUT_HPP
