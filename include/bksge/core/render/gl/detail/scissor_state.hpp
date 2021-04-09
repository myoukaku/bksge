/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_SCISSOR_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_SCISSOR_STATE_HPP

#include <bksge/core/render/fwd/scissor_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class ScissorState
{
public:
	static void Apply(bksge::ScissorState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/scissor_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_SCISSOR_STATE_HPP
