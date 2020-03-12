/**
 *	@file	glsl_uniform_block.hpp
 *
 *	@brief	GlslUniformBlock クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GLSL_UNIFORM_BLOCK_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GLSL_UNIFORM_BLOCK_HPP

#include <bksge/core/render/gl/detail/fwd/glsl_uniform_block_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_parameter_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <vector>
#include <string>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class GlslUniformBlock
{
public:
	explicit GlslUniformBlock(::GLuint program, ::GLint uniform_block_index);

	~GlslUniformBlock();

	void LoadParameter(
		bksge::ShaderParameterMap const& shader_parameter_map,
		std::vector<GlslParameterUnique> const& parameters);

private:
	// noncopyable
	GlslUniformBlock(GlslUniformBlock const&) = delete;
	GlslUniformBlock& operator=(GlslUniformBlock const&) = delete;

private:
	std::string				m_name;
	::GLint					m_size = 0;
	::GLint					m_binding = 0;
	UniformBufferUnique		m_uniform_buffer;
	std::vector<::GLint>	m_member_indices;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_uniform_block_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_UNIFORM_BLOCK_HPP
