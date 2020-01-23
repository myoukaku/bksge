/**
 *	@file	glsl_uniform_block_inl.hpp
 *
 *	@brief	GlslUniformBlock クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_UNIFORM_BLOCK_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_UNIFORM_BLOCK_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/glsl_uniform_block.hpp>
#include <bksge/core/render/gl/detail/glsl_parameter.hpp>
#include <bksge/core/render/gl/detail/uniform_buffer.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslUniformBlock::GlslUniformBlock(::GLuint program, ::GLint uniform_block_index)
{
	{
		::GLint name_length;
		::glGetActiveUniformBlockiv(program, uniform_block_index, GL_UNIFORM_BLOCK_NAME_LENGTH, &name_length);

		std::vector<::GLchar> buf(name_length + 1);
		::glGetActiveUniformBlockName(program, uniform_block_index, name_length, nullptr, buf.data());
		m_name = buf.data();
	}

	::glGetActiveUniformBlockiv(program, uniform_block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &m_size);
	::glGetActiveUniformBlockiv(program, uniform_block_index, GL_UNIFORM_BLOCK_BINDING, &m_binding);

	m_uniform_buffer =
		bksge::make_unique<gl::UniformBuffer>(nullptr, m_size, m_binding);

	::glUniformBlockBinding(program, uniform_block_index, m_binding);

	::GLint member_num = 0;
	::glGetActiveUniformBlockiv(program, uniform_block_index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &member_num);

	m_member_indices.resize(member_num);
	::glGetActiveUniformBlockiv(program, uniform_block_index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, m_member_indices.data());
}

BKSGE_INLINE
GlslUniformBlock::~GlslUniformBlock()
{
}

BKSGE_INLINE void
GlslUniformBlock::LoadParameter(
	bksge::ShaderParameterMap const& shader_parameter_map,
	std::vector<GlslParameterUnique> const& parameters)
{
	m_uniform_buffer->Bind();

	// Uniform Block をまとめて更新
	{
		auto param = shader_parameter_map[m_name];
		if (param)
		{
			::glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, param->data());
		}
	}

	// Uniform Block のメンバーを個別に更新
	for (auto index : m_member_indices)
	{
		parameters[index]->LoadUniformBuffer(shader_parameter_map);
	}

	m_uniform_buffer->Unbind();
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_UNIFORM_BLOCK_INL_HPP
