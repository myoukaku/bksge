/**
 *	@file	gl_shader_program_fwd.hpp
 *
 *	@brief	GlShaderProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_SHADER_PROGRAM_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_SHADER_PROGRAM_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

class GlShaderProgram;
using GlShaderProgramUnique = std::unique_ptr<GlShaderProgram>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_SHADER_PROGRAM_FWD_HPP
