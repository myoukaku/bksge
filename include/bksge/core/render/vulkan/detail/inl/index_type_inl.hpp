/**
 *	@file	index_type_inl.hpp
 *
 *	@brief	IndexType の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_TYPE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_TYPE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/index_type.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/detail/type_enum.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkIndexType
ToVulkanIndexType(bksge::TypeEnum type)
{
	switch (type)
	{
	case bksge::TypeEnum::kUInt16:
		return VK_INDEX_TYPE_UINT16;

	case bksge::TypeEnum::kUInt32:
		return VK_INDEX_TYPE_UINT32;

	default:
		// TODO エラーにする
		return VK_INDEX_TYPE_UINT16;
	}
}

}	// namespace detail

BKSGE_INLINE
IndexType::IndexType(bksge::TypeEnum type)
	: m_index_type(detail::ToVulkanIndexType(type))
{}

BKSGE_INLINE
IndexType::operator ::VkIndexType() const
{
	return m_index_type;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_TYPE_INL_HPP
