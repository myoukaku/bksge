/**
 *	@file	shader_stage_inl.hpp
 *
 *	@brief	ShaderStage の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SHADER_STAGE_INL_HPP
#define BKSGE_RENDER_INL_SHADER_STAGE_INL_HPP

#include <bksge/render/shader_stage.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(ShaderStage const& shader_stage)
{
#define BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(x)	{ x, #x }

	static std::unordered_map<ShaderStage, std::string> const m =
	{
		BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(ShaderStage::kVertex),
		BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(ShaderStage::kGeometry),
		BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(ShaderStage::kFragment),
		BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(ShaderStage::kTessellationControl),
		BKSGE_RENDER_MAKE_SHADER_STAGE_KVP(ShaderStage::kTessellationEvaluation),
	};

	return m.at(shader_stage);

#undef BKSGE_RENDER_MAKE_SHADER_STAGE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SHADER_STAGE_INL_HPP
