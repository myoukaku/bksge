/**
 *	@file	shader_type_inl.hpp
 *
 *	@brief	ShaderType の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SHADER_TYPE_INL_HPP
#define BKSGE_CORE_RENDER_INL_SHADER_TYPE_INL_HPP

#include <bksge/core/render/shader_type.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(ShaderType const& shader_type)
{
#define BKSGE_CORE_RENDER_MAKE_SHADER_TYPE_KVP(x)	{ x, #x }

	static std::unordered_map<ShaderType, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_SHADER_TYPE_KVP(ShaderType::kHLSL),
		BKSGE_CORE_RENDER_MAKE_SHADER_TYPE_KVP(ShaderType::kGLSL),
	};

	return m.at(shader_type);

#undef BKSGE_CORE_RENDER_MAKE_SHADER_TYPE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SHADER_TYPE_INL_HPP
