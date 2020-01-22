/**
 *	@file	glsl_uniform_block_fwd.hpp
 *
 *	@brief	GlslUniformBlock クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_UNIFORM_BLOCK_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_UNIFORM_BLOCK_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

class GlslUniformBlock;
using GlslUniformBlockUnique = std::unique_ptr<GlslUniformBlock>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GLSL_UNIFORM_BLOCK_FWD_HPP
