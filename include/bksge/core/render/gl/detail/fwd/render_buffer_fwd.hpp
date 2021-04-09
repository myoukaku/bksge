/**
 *	@file	render_buffer_fwd.hpp
 *
 *	@brief	RenderBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_RENDER_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_RENDER_BUFFER_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class RenderBuffer;
using RenderBufferShared = bksge::shared_ptr<RenderBuffer>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_RENDER_BUFFER_FWD_HPP
