/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP

#include <bksge/core/render/fwd/blend_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class BlendState
{
public:
	static void Apply(bksge::BlendState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_BLEND_STATE_HPP
