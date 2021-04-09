/**
 *	@file	frame_buffer_fwd.hpp
 *
 *	@brief	FrameBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_FRAME_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_FRAME_BUFFER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class FrameBuffer;
using FrameBufferUnique = bksge::unique_ptr<FrameBuffer>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_FRAME_BUFFER_FWD_HPP
