/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_FACTOR_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_FACTOR_HPP

#include <bksge/core/render/fwd/blend_factor_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class BlendFactor
{
public:
	explicit BlendFactor(bksge::BlendFactor blend_factor);

	operator ::VkBlendFactor() const;

private:
	::VkBlendFactor	m_blend_factor;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/blend_factor_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_FACTOR_HPP
