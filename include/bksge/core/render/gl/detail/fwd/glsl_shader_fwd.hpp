/**
 *	@file	glsl_shader_fwd.hpp
 *
 *	@brief	GlslShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_SHADER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_SHADER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslShader;
using GlslShaderUnique = std::unique_ptr<GlslShader>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_SHADER_FWD_HPP
