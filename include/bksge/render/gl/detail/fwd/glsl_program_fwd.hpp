﻿/**
 *	@file	glsl_program_fwd.hpp
 *
 *	@brief	GlslProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP
#define BKSGE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslProgram;
using GlslProgramShared = std::shared_ptr<GlslProgram>;
using GlslProgramMap    = std::map<Identifier, GlslProgramShared>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP
