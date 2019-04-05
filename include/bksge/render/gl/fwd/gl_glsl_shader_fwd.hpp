/**
 *	@file	gl_glsl_shader_fwd.hpp
 *
 *	@brief	GlGLSLShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_GLSL_SHADER_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_GLSL_SHADER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

class GlGLSLShader;
using GlGLSLShaderUnique = std::unique_ptr<GlGLSLShader>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_GLSL_SHADER_FWD_HPP
