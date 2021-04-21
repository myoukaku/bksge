/**
 *	@file	descriptor_set.hpp
 *
 *	@brief	DescriptorSet クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP

#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>

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
		vulkan::DescriptorPoolSharedPtr const& descriptor_pool,
		bksge::vector<::VkDescriptorSetLayout> const& descriptor_set_layout);

	~DescriptorSet();

	bksge::vector<::VkDescriptorSet> const& Get(void) const;

private:
	// noncopyable
	DescriptorSet(DescriptorSet const&) = delete;
	DescriptorSet& operator=(DescriptorSet const&) = delete;

private:
	vulkan::DescriptorPoolSharedPtr			m_descriptor_pool;
	bksge::vector<::VkDescriptorSet>		m_descriptor_sets;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/descriptor_set_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DESCRIPTOR_SET_HPP
