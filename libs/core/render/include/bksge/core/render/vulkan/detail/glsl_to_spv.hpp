/**
 *	@file	glsl_to_spv.hpp
 *
 *	@brief	GlslToSpv 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_GLSL_TO_SPV_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_GLSL_TO_SPV_HPP

#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

bksge::vector<unsigned int>
GlslToSpv(::VkShaderStageFlagBits shader_type, const char* source);

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/glsl_to_spv_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_GLSL_TO_SPV_HPP
