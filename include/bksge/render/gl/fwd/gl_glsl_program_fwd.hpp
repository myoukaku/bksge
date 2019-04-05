/**
 *	@file	gl_glsl_program_fwd.hpp
 *
 *	@brief	GlGLSLProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_GLSL_PROGRAM_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_GLSL_PROGRAM_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class GlGLSLProgram;
using GlGLSLProgramShared = std::shared_ptr<GlGLSLProgram>;
using GlGLSLProgramMap    = std::map<Identifier, GlGLSLProgramShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_GLSL_PROGRAM_FWD_HPP
