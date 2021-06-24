/**
 *	@file	stencil_state.hpp
 *
 *	@brief	StencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP

#include <bksge/core/render/fwd/stencil_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class StencilState
{
public:
	static void Apply(bksge::StencilState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/stencil_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_STENCIL_STATE_HPP
