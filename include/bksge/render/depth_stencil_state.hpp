/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DEPTH_STENCIL_STATE_HPP
#define BKSGE_RENDER_DEPTH_STENCIL_STATE_HPP

#include <bksge/render/fwd/depth_stencil_state_fwd.hpp>

namespace bksge
{

namespace render
{

class DepthStencilState
{
public:
private:
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/depth_stencil_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_DEPTH_STENCIL_STATE_HPP
