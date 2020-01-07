/**
 *	@file	bool_inl.hpp
 *
 *	@brief	Bool の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BOOL_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BOOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/bool.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Bool::Bool(bool b)
	: m_bool(b ? VK_TRUE : VK_FALSE)
{}

BKSGE_INLINE
Bool::operator VkBool32() const
{
	return m_bool;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BOOL_INL_HPP
