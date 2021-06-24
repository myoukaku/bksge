/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PRIMITIVE_TOPOLOGY_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PRIMITIVE_TOPOLOGY_HPP

#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class PrimitiveTopology
{
public:
	explicit PrimitiveTopology(bksge::PrimitiveTopology primitive_topology);

	operator ::VkPrimitiveTopology() const;

private:
	::VkPrimitiveTopology	m_primitive_topology;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/primitive_topology_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PRIMITIVE_TOPOLOGY_HPP
