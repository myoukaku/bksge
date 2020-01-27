/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP

#include <bksge/core/render/shader_stage.hpp>
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
class ShaderStage
{
public:
	explicit ShaderStage(bksge::ShaderStage shader_stage);

	operator ::VkShaderStageFlagBits() const;

private:
	::VkShaderStageFlagBits	m_shader_stage;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP
