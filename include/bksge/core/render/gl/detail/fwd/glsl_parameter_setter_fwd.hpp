/**
 *	@file	glsl_parameter_setter_fwd.hpp
 *
 *	@brief	GlslParameterSetter クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_SETTER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_SETTER_FWD_HPP

#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslParameterSetterBase;

template <::GLenum Type>
class GlslParameterSetter;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_SETTER_FWD_HPP
