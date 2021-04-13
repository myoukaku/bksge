/**
 *	@file	vertex_format.hpp
 *
 *	@brief	VertexFormat クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_FORMAT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_FORMAT_HPP

#include <bksge/core/render/detail/vertex_attribute.hpp>
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
class VertexFormat
{
public:
	explicit VertexFormat(
		bksge::render::VertexAttribute const& vertex_format);

	operator ::VkFormat() const;

private:
	::VkFormat	m_format;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/vertex_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_FORMAT_HPP
