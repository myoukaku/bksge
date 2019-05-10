/**
 *	@file	shader_map.hpp
 *
 *	@brief	ShaderMap クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_SHADER_MAP_HPP
#define BKSGE_RENDER_SHADER_MAP_HPP

#include <bksge/render/fwd/shader_map_fwd.hpp>
#include <bksge/render/shader_type.hpp>
#include <bksge/render/shader.hpp>
#include <map>
#include <initializer_list>
#include <utility>	// pair

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class ShaderMap
{
public:
	ShaderMap(std::initializer_list<std::pair<ShaderType, Shader&&>> il);

	// コピー禁止
	ShaderMap(ShaderMap const&) = delete;
	ShaderMap& operator=(ShaderMap const&) = delete;

	// ムーブ可能
	ShaderMap(ShaderMap&& rhs);
	ShaderMap& operator=(ShaderMap&& rhs);

	~ShaderMap() = default;

	Shader const* GetShader(ShaderType type) const;

private:
	std::map<ShaderType, Shader>	m_shaders;

private:
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/shader_map_inl.hpp>
#endif

#endif // BKSGE_RENDER_SHADER_MAP_HPP
