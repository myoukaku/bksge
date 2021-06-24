/**
 *	@file	front_face_inl.hpp
 *
 *	@brief	FrontFace の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRONT_FACE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRONT_FACE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/front_face.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/front_face.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkFrontFace
ToVulkanFrontFace(bksge::FrontFace front_face)
{
	switch (front_face)
	{
	case bksge::FrontFace::kClockwise:        return VK_FRONT_FACE_CLOCKWISE;
	case bksge::FrontFace::kCounterClockwise: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
	}
	return VK_FRONT_FACE_COUNTER_CLOCKWISE;
}

}	// namespace detail

BKSGE_INLINE
FrontFace::FrontFace(bksge::FrontFace front_face)
	: m_front_face(detail::ToVulkanFrontFace(front_face))
{}

BKSGE_INLINE
FrontFace::operator ::VkFrontFace() const
{
	return m_front_face;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRONT_FACE_INL_HPP
