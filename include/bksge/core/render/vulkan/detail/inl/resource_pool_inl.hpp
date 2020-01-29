/**
 *	@file	resource_pool_inl.hpp
 *
 *	@brief	ResourcePool クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/combined_image_sampler.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <memory>	// make_shared
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

template <typename Ret, typename Map, typename Id, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Id const& id, Args&&... args)
{
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourcePool::ResourcePool(void)
{
}

BKSGE_INLINE
ResourcePool::~ResourcePool()
{
}

BKSGE_INLINE vulkan::ShaderSharedPtr
ResourcePool::GetShader(
	vulkan::DeviceSharedPtr const& device,
	bksge::Shader const& shader)
{
	return detail::GetOrCreate<vulkan::Shader>(
		m_shader_map, shader.id(), device, shader);
}

BKSGE_INLINE vulkan::GeometrySharedPtr
ResourcePool::GetGeometry(
	vulkan::DeviceSharedPtr const& device,
	bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<vulkan::Geometry>(
		m_geometry_map, geometry.id(), device, geometry);
}

BKSGE_INLINE vulkan::GraphicsPipelineSharedPtr
ResourcePool::GetGraphicsPipeline(
	vulkan::DeviceSharedPtr const& device,
	::VkSampleCountFlagBits num_samples,
	bksge::Geometry const& geometry,
	bksge::Shader const& shader,
	bksge::RenderState const& render_state,
	vulkan::RenderPass const& render_pass)
{
	auto const id = bksge::hash_combine(
		static_cast<std::uint32_t>(num_samples),
		geometry.id(),
		shader.id(),
		render_state);

	return detail::GetOrCreate<vulkan::GraphicsPipeline>(
		m_graphics_pipeline_map,
		id,
		device,
		num_samples,
		geometry,
		render_state,
		render_pass,
		*(this->GetShader(device, shader)));
}

BKSGE_INLINE vulkan::CombinedImageSamplerSharedPtr
ResourcePool::GetCombinedImageSampler(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Sampler const& sampler)
{
	return detail::GetOrCreate<vulkan::CombinedImageSampler>(
		m_combined_image_sampler_map, sampler.id(), device, command_pool, sampler);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_POOL_INL_HPP
