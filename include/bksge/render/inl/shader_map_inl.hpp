/**
 *	@file	shader_map_inl.hpp
 *
 *	@brief	ShaderMap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SHADER_MAP_INL_HPP
#define BKSGE_RENDER_INL_SHADER_MAP_INL_HPP

#include <bksge/render/shader_map.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ShaderMap::ShaderMap(std::initializer_list<std::pair<ShaderType, Shader&&>> il)
{
	for (auto& i : il)
	{
		m_shaders.emplace(i.first, std::move(i.second));
	}
}

BKSGE_INLINE Shader const*
ShaderMap::GetShader(ShaderType type) const
{
	auto it = m_shaders.find(type);
	if (it == m_shaders.end())
	{
		return nullptr;
	}

	return &it->second;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SHADER_MAP_INL_HPP
