/**
 *	@file	glsl_program_fwd.hpp
 *
 *	@brief	GlslProgram クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/map/map.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslProgram;
using GlslProgramShared = bksge::shared_ptr<GlslProgram>;
using GlslProgramMap    = bksge::map<Identifier, GlslProgramShared>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PROGRAM_FWD_HPP
