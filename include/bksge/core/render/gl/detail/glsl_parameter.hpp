/**
 *	@file	glsl_parameter.hpp
 *
 *	@brief	GlslParameter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP

#include <bksge/core/render/gl/detail/fwd/glsl_parameter_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_parameter_setter_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/string/string.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class GlslParameter
{
public:
	explicit GlslParameter(::GLuint program, ::GLuint index);

	~GlslParameter();

	void LoadParameter(
		ResourcePool* resource_pool,
		bksge::ShaderParameterMap const& shader_parameter_map);

	void LoadUniformBuffer(
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	// noncopyable
	GlslParameter(GlslParameter const&) = delete;
	GlslParameter& operator=(GlslParameter const&) = delete;

private:
	bksge::string	m_name;
	::GLint			m_size;
	::GLenum		m_type;
	::GLint			m_location;
	::GLint			m_offset;
	bksge::unique_ptr<GlslParameterSetterBase>	m_setter;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_parameter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP
