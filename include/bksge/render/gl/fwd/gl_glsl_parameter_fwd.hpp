/**
 *	@file	gl_glsl_parameter_fwd.hpp
 *
 *	@brief	GlGLSLParameter クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_GLSL_PARAMETER_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_GLSL_PARAMETER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

class GlGLSLParameter;
using GlGLSLParameterUnique = std::unique_ptr<GlGLSLParameter>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_GLSL_PARAMETER_FWD_HPP
