/**
 *	@file	glsl_parameter_fwd.hpp
 *
 *	@brief	GlslParameter クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslParameter;
using GlslParameterUnique = bksge::unique_ptr<GlslParameter>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_PARAMETER_FWD_HPP
