/**
 *	@file	glsl_program.hpp
 *
 *	@brief	GlslProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP

#include <bksge/core/render/gl/detail/fwd/glsl_program_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_shader_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_parameter_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_uniform_block_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
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
		ResourcePool* resource_pool,
		Geometry const* geometry,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	// noncopyable
	GlslProgram(GlslProgram const&) = delete;
	GlslProgram& operator=(GlslProgram const&) = delete;

private:
	void LoadParameters(
		ResourcePool* resource_pool,
		bksge::ShaderParameterMap const& shader_parameter_map);

	using GlslShaders    = std::vector<GlslShaderUnique>;
	using GlslParameters = std::vector<GlslParameterUnique>;
	using GlslUniformBlocks = std::vector<GlslUniformBlockUnique>;

	::GLuint		m_id;
	GlslShaders		m_shaders;
	GlslParameters	m_parameters;
	GlslUniformBlocks	m_uniform_blocks;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_program_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PROGRAM_HPP
