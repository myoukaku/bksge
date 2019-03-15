/**
 *	@file	gl_shader_fwd.hpp
 *
 *	@brief	GlShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_SHADER_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_SHADER_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class GlShader;
using GlShaderShared = std::shared_ptr<GlShader>;
using GlShaderMap    = std::map<Identifier, GlShaderShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_SHADER_FWD_HPP
