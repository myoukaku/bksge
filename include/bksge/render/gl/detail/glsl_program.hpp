/**
 *	@file	glsl_program.hpp
 *
 *	@brief	GlslProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP
#define BKSGE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP

#include <bksge/render/gl/detail/fwd/glsl_program_fwd.hpp>
#include <bksge/render/gl/detail/fwd/glsl_shader_fwd.hpp>
#include <bksge/render/gl/detail/fwd/glsl_parameter_fwd.hpp>
#include <bksge/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/render/gl/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class GlslProgram
{
public:
	explicit GlslProgram(bksge::Shader const& shader);

	~GlslProgram();

	void Render(
		ResourceCache* resource_cache,
		Geometry const* geometry,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	void LoadParameters(
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

	using GlslShaders    = std::vector<GlslShaderUnique>;
	using GlslParameters = std::vector<GlslParameterUnique>;

	::GLuint		m_id;
	GlslShaders		m_shaders;
	GlslParameters	m_parameters;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/glsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP
