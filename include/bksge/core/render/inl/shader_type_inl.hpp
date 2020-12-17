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
#include <bksge/fnd/config.hpp>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(ShaderType const& shader_type)
{
#define BKSGE_CORE_RENDER_SHADER_TYPE_KVP(x)	case x: return #x

	switch (shader_type)
	{
		BKSGE_CORE_RENDER_SHADER_TYPE_KVP(ShaderType::kHLSL);
		BKSGE_CORE_RENDER_SHADER_TYPE_KVP(ShaderType::kGLSL);
	}

	return "";

#undef BKSGE_CORE_RENDER_SHADER_TYPE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SHADER_TYPE_INL_HPP
