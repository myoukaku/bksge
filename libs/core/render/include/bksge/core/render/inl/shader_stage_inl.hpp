/**
 *	@file	shader_stage_inl.hpp
 *
 *	@brief	ShaderStage の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SHADER_STAGE_INL_HPP
#define BKSGE_CORE_RENDER_INL_SHADER_STAGE_INL_HPP

#include <bksge/core/render/shader_stage.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(ShaderStage const& shader_stage)
{
#define BKSGE_CORE_RENDER_SHADER_STAGE_KVP(x)	case x: return #x

	switch (shader_stage)
	{
		BKSGE_CORE_RENDER_SHADER_STAGE_KVP(ShaderStage::kVertex);
		BKSGE_CORE_RENDER_SHADER_STAGE_KVP(ShaderStage::kGeometry);
		BKSGE_CORE_RENDER_SHADER_STAGE_KVP(ShaderStage::kFragment);
		BKSGE_CORE_RENDER_SHADER_STAGE_KVP(ShaderStage::kTessellationControl);
		BKSGE_CORE_RENDER_SHADER_STAGE_KVP(ShaderStage::kTessellationEvaluation);
	}

	return "";

#undef BKSGE_CORE_RENDER_SHADER_STAGE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SHADER_STAGE_INL_HPP
