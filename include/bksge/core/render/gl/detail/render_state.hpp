/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RENDER_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RENDER_STATE_HPP

#include <bksge/core/render/fwd/render_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class RenderState
{
public:
	static void Apply(bksge::RenderState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/render_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RENDER_STATE_HPP
