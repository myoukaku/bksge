/**
 *	@file	combined_image_sampler_setter_inl.hpp
 *
 *	@brief	CombinedImageSamplerSetter クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_SETTER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_SETTER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/combined_image_sampler_setter.hpp>
#include <bksge/core/render/vulkan/detail/combined_image_sampler.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/utility/pair.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
CombinedImageSamplerSetter::CombinedImageSamplerSetter(
	vulkan::ShaderReflectionUniform const& reflection)
{
	m_set             = reflection.set;
	m_binding         = reflection.binding;
	m_name            = reflection.name;
	m_descriptor_type = reflection.descriptor_type;

	m_image_info.sampler     = VK_NULL_HANDLE;
	m_image_info.imageView   = VK_NULL_HANDLE;
	m_image_info.imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
}

BKSGE_INLINE
CombinedImageSamplerSetter::~CombinedImageSamplerSetter()
{
}

BKSGE_INLINE void
CombinedImageSamplerSetter::LoadParameters(
	bksge::ShaderParameterMap const& shader_parameter_map,
	vulkan::CommandPoolSharedPtr const& command_pool,
	vulkan::UniformBuffer* /*uniform_buffer*/,
	vulkan::ResourcePool* resource_pool)
{
	auto param = shader_parameter_map[m_name];
	if (!param || !param->data())
	{
		return;
	}

	using Sampler2d = bksge::pair<bksge::Sampler, bksge::Texture>;
	if (param->class_id() == ShaderParameter<Sampler2d>::StaticClassId())
	{
		auto sampler_2d = static_cast<Sampler2d const*>(param->data());
		auto sampler = resource_pool->GetSampler(sampler_2d->first);
		auto image   = resource_pool->GetImage(sampler_2d->second, command_pool);
		vulkan::CombinedImageSampler const combined_image_sampler(sampler, image);
		m_image_info = combined_image_sampler.GetImageInfo();
		return;
	}

	if (param->class_id() == ShaderParameter<vulkan::CombinedImageSampler>::StaticClassId())
	{
		auto combined_image_sampler =
			static_cast<vulkan::CombinedImageSampler const*>(param->data());
		m_image_info = combined_image_sampler->GetImageInfo();
		return;
	}
}

BKSGE_INLINE vk::WriteDescriptorSet
CombinedImageSamplerSetter::GetWriteDescriptorSet(void) const
{
	vk::WriteDescriptorSet write;
	write.dstSet           = VK_NULL_HANDLE;
	write.dstBinding       = m_binding;
	write.dstArrayElement  = 0;
	write.descriptorCount  = 1;
	write.descriptorType   = m_descriptor_type;
	write.pImageInfo       = &m_image_info;
	write.pBufferInfo      = nullptr;
	write.pTexelBufferView = nullptr;

	return write;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_SETTER_INL_HPP
