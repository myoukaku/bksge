/**
 *	@file	glsl_parameter.hpp
 *
 *	@brief	GlslParameter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP
#define BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP

#include <bksge/render/gl/detail/fwd/glsl_parameter_fwd.hpp>
#include <bksge/render/gl/detail/fwd/glsl_parameter_setter_fwd.hpp>
#include <bksge/render/gl/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <memory>

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
	explicit GlslParameter(::GLuint program, ::GLint index);

	~GlslParameter();

	void LoadParameter(
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	std::string		m_name;
	::GLint			m_size;
	::GLenum		m_type;
	::GLint			m_location;
	std::unique_ptr<GlslParameterSetterBase>	m_setter;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/glsl_parameter_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_HPP
